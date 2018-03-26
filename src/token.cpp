#include "include/token.h"


// 设置两个栈，一个存操作数(operand)，一个存操作符(operator)
// 每个token有processor方法，从输入中依次读到该token时调用
//    对于数，直接放入操作数栈
//    对于操作符，从操作符栈pop直到不应该pop，对每个pop出的操作符执行calculate方法。最后将自己push进操作符栈

namespace token_list {

bool token_node::should_pop(token_node* top, token_node* next) {
#ifdef debug
  std::cerr << "should pop : ";
#endif
  if (dynamic_cast<leftparen_node*>(next) || dynamic_cast<unaryop_node*>(next)) {
#ifdef debug
    std::cerr << "next is ( or unary, don't pop" << std::endl;
#endif
    return false;
  }
  if (dynamic_cast<end_node*>(next)) {
#ifdef debug
    std::cerr << "next is end, pop\n";
#endif
    return true;
  } else {
    auto next_op = dynamic_cast<binop_node*>(next);
    if (next_op) {
      auto top_op = dynamic_cast<binop_node*>(top);
      if (top_op) {
#ifdef debug
        std::cerr << "all is binop, decide ur self\n";
#endif
        switch(next_op->op) {
          case bin_op::exponentiation : 
            return (int)top_op->op >= (int)bin_op::exponentiation;
          case bin_op::modulo :
            return (int)top_op->op >= (int)bin_op::modulo;
          case bin_op::divide : 
            return (int)top_op->op >= (int)bin_op::multiply;
          case bin_op::multiply : 
            return (int)top_op->op >= (int)bin_op::multiply;
          case bin_op::minus :
          case bin_op::plus :
            return true;
        }
      } else {
#ifdef debug
        std::cerr << "next is op, top is not, don't pop\n";
#endif
        return false;
      }
    } else {
      throw("syntax error!\n");
    }
  }
}

void number_node::processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) {
#ifdef debug
  std::cerr << "processing a number " << dynamic_cast<float_node*>(this)->value << std::endl;
#endif
  ptr<number_node> p(this);
  operands.push(p); 
}

void operator_node::processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) {
#ifdef debug
  std::cerr << "processing a operator\n";
#endif
  while (!operators.empty() && this->should_pop(operators.top().get(), this)) {
#ifdef debug
    std::cerr << "pop one from operators\n";
#endif
    operators.top()->calculate(operands);
    operators.pop();
  }
  ptr<operator_node> p(this);
  operators.push(p);
}

void rightparen_node::processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) {
#ifdef debug
  std::cerr << "processing a )\n";
#endif
  while (true) {
    auto top = operators.top();
    if (!top) {
      throw("syntax error!\n");
    }
    if (dynamic_cast<unaryop_node*>(top.get()) || dynamic_cast<leftparen_node*>(top.get())) {
#ifdef debug
      std::cerr << "top is unary or (\n";
#endif 
      top->calculate(operands);
      operators.pop();
      return;
    } else {
#ifdef debug
      std::cerr << "top is binop\n";
#endif
      top->calculate(operands);
      operators.pop();

    }
  }
}

void binop_node::calculate(std::stack<ptr<token_node>> &operands) {
  if (operands.empty()) {
    throw("syntax error!\n");
  }
  auto op2 = dynamic_cast<float_node*>(operands.top().get())->value;
  operands.pop();
  if (operands.empty()) {
    throw("syntax error!\n");
  };
  auto op1 = dynamic_cast<float_node*>(operands.top().get())->value;
  operands.pop(); 
  ptr<float_node> p(new float_node);
  switch(this->op) {
    case bin_op::plus: 
      p->value = op1 + op2;
      break;
    case bin_op::minus:
      p->value = op1 - op2;
      break;
    case bin_op::multiply :
      p->value = op1 * op2;
      break;
    case bin_op::divide : 
      p->value = op1 / op2;
      break;
    case bin_op::modulo : 
      p->value = round(op1) % round(op2);
      break;
    case bin_op::exponentiation : 
      p->value = powl(op1, op2);
      break;
  }
#ifdef debug
  std::cerr << "calculating bin op " << this->op << " with operand " << op1 << " " << op2 << " and result is " << p->value << std::endl;
#endif
  operands.push(p);
}

void unaryop_node::calculate(std::stack<ptr<token_node>> &operands) {
  if (operands.empty()) {
    throw("syntax error!\n");
  }
  auto op = dynamic_cast<float_node*>(operands.top().get())->value;
  operands.pop();
  ptr<float_node> p(new float_node);
  switch(this->op) {
    case unary_op::positive : {
      p->value = op;
      break;
    }
    case unary_op::negative : {
      p->value = -op;
      break;
    }
    case unary_op::sin : {
      p->value = sinl(op);
      break;
    }
    case unary_op::cos : {
      p->value = cosl(op);
      break;
    }
    case unary_op::tan : {
      p->value = tanl(op);
      break;
    }
    case unary_op::sqrt : {
      p->value = sqrtl(op);
      break;
    }
    case unary_op::factorial : {
      int t = round(op);
      int rst = 1;
      while (t > 1) {
        rst *= t;
        t--;
      }
      p->value = rst;
      break;
    }
    case unary_op::logarithm : {
      p->value = logl(op);
      break;
    }
    default :
      throw("syntax error!\n");
  }
#ifdef debug
  std::cerr << "calculating bin op " << this->op << " with operand " << op << " and result is " << p->value << std::endl ; 
#endif
  operands.push(p);
}

void insert(std::vector<token_list::token_node*> &list, double n) {
    auto node = new token_list::float_node;
    node->value = n;
    list.push_back(node);
}
void insert(std::vector<token_list::token_node*> &list, token_list::bin_op op) {
    auto node = new token_list::binop_node;
    node->op = op;
    list.push_back(node);
}
void insert(std::vector<token_list::token_node*> &list, token_list::unary_op op) {
    auto node = new token_list::unaryop_node;
    node->op = op;
    list.push_back(node);
}

double List::calculate() {
  for (auto t : list_) {
    t->processor(operators, operands);
  }
  if (operands.size() != 1) {
    throw("syntax error!\n");
  }
  return dynamic_cast<float_node*>(operands.top().get())->value;
}

// List& operator<<(List& me, token_list::unary_op op) {
//   insert(me.list_, op);
//   return me;
// }    

// List& operator<<(List& me, token_list::bin_op op) {
//   insert(me.list_, op);
//   return me;
// }

List& operator<<(List& me, double n) {
  insert(me.list_, n);
  return me;
}
List& operator<<(List& me, int n) {
  insert(me.list_, (double)n);
  return me;
}
List& operator<<(List& me, std::string s) {
  if (s == "+") {
    if (dynamic_cast<token_list::number_node*>(me.list_.back()) || dynamic_cast<token_list::rightparen_node*>(me.list_.back())) {
      insert(me.list_, token_list::plus);
    } else {
      insert(me.list_, token_list::positive);
    }
  } else if (s == "-") {
    if (dynamic_cast<token_list::number_node*>(me.list_.back()) || dynamic_cast<token_list::rightparen_node*>(me.list_.back())) {
      insert(me.list_, token_list::minus);
    } else {
      insert(me.list_, token_list::negative);
    }
  } else if (s == "*") {
    insert(me.list_, token_list::multiply);
  } else if (s == "/") {
    insert(me.list_, token_list::divide);
  } else if (s == "%") {
    insert(me.list_, token_list::modulo);
  } else if (s == "^") {
    insert(me.list_, token_list::exponentiation);
  } else if (s == "sin") {
    insert(me.list_, token_list::sin);
  } else if (s == "cos") {
    insert(me.list_, token_list::cos);
  } else if (s == "tan") {
    insert(me.list_, token_list::tan);
  } else if (s == "!") {
    insert(me.list_, token_list::factorial);
  } else if (s == "ln") {
    insert(me.list_, token_list::logarithm);
  } else if (s == "(") {
    me.list_.push_back(new token_list::leftparen_node);
  } else if (s == ")") {
    me.list_.push_back(new token_list::rightparen_node);
  } else if (s == "end") {
    me.list_.push_back(new token_list::end_node);
  }
  return me;
}

} //namespace token_list
