#include "token.h"


// 设置两个栈，一个存操作数(operand)，一个存操作符(operator)
// 每个token有processor方法，从输入中依次读到该token时调用
//    对于数，直接放入操作数栈
//    对于操作符，从操作符栈pop直到不应该pop，对每个pop出的操作符执行calculate方法。最后将自己push进操作符栈

namespace token_list {

bool token_node::should_pop(token_node* top, token_node* next) {
  std::cerr << "should pop : ";
  if (dynamic_cast<leftparen_node*>(next) || dynamic_cast<unaryop_node*>(next)) {
    std::cerr << "next is ( or unary, don't pop" << std::endl;
    return false;
  }
  // if (dynamic_cast<rightparen_node*>(next)) {
    // if (dynamic_cast<leftparen_node*>(top) || dynamic_cast<unaryop_node*>(top)) {
      // return false;
    // } else {
      // return true;
    // }
  // } else 
  if (dynamic_cast<end_node*>(next)) {
    std::cerr << "next is end, pop\n";
    return true;
  } else {
    auto next_op = dynamic_cast<binop_node*>(next);
    if (next_op) {
      auto top_op = dynamic_cast<binop_node*>(top);
      if (top_op) {
        std::cerr << "all is binop, decide ur self\n";
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
        std::cerr << "next is op, top is not, don't pop\n";
        return false;
      }
    } else {
      exit(1);
    }
  }
}

void number_node::processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) {
  std::cerr << "processing a number " << dynamic_cast<float_node*>(this)->value << std::endl;
  ptr<number_node> p(this);
  operands.push(p); 
}

void operator_node::processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) {
  std::cerr << "processing a operator\n";
  while (!operators.empty() && this->should_pop(operators.top().get(), this)) {
    std::cerr << "pop one from operators\n";
    auto rst = operators.top()->calculate(operands);
    if (rst) {
      std::cerr << "get a result " << dynamic_cast<float_node*>(rst.get()) << ", push to operands\n";
      operands.push(rst);
    }
    operators.pop();
  }
  // if (dynamic_cast<rightparen_node*>(this)) return;
  ptr<operator_node> p(this);
  operators.push(p);
}

void rightparen_node::processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) {
  std::cerr << "processing a (\n";
  while (true) {
    auto top = operators.top();
    if (!top) exit(1);
    if (dynamic_cast<unaryop_node*>(top.get()) || dynamic_cast<leftparen_node*>(top.get())) {
      std::cerr << "top is unary or (\n";
      auto rst = top->calculate(operands);
      std::cerr << "get a result " << dynamic_cast<float_node*>(rst.get()) << ", push to operands\n";
      operands.push(rst);
      operators.pop();
      return;
    } else {
      std::cerr << "top is binop\n";
      auto rst = top->calculate(operands);
      std::cerr << "get a result " << dynamic_cast<float_node*>(rst.get()) << ", push to operands\n";
      operands.push(rst);
      operators.pop();

    }
  }
}

ptr<token_node> binop_node::calculate(std::stack<ptr<token_node>> &operands) {
  if (operands.empty()) exit(1);
  auto op2 = dynamic_cast<float_node*>(operands.top().get())->value;
  operands.pop();
  if (operands.empty()) exit(1);
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
      p->value = int(op1) % int(op2);
      break;
    case bin_op::exponentiation : 
      p->value = powl(op1, op2);
      break;
  }
  return p;
}

ptr<token_node> unaryop_node::calculate(std::stack<ptr<token_node>> &operands) {
  if (operands.empty()) exit(1);
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
      int t = int(op);
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
      exit(1);
  }
  return p;
}


}