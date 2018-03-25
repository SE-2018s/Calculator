#include "token.h"

// 设置两个栈，一个存操作数(operand)，一个存操作符(operator)
// 每个token有processor方法，从输入中依次读到该token时调用
//    对于数，直接放入操作数栈
//    对于操作符，从操作符栈pop直到不应该pop，对每个pop出的操作符执行calculate方法。最后将自己push进操作符栈

namespace token_list {

void number_node::processor(std::stack<ptr<operator_node>> &operators, std::stack<ptr<number_node>> &operands) {
  ptr<number_node> p(this);
  operands.push(p); 
}

void operator_node::processor(std::stack<ptr<operator_node>> &operators, std::stack<ptr<number_node>> &operands) {
  while (this->should_pop(operators.top().get(), this)) {
    operands.push(operators.top()->calculate(operands));
    operators.pop();
  }
  ptr<operator_node> p(this);
  operators.push(p);
}

ptr<number_node> binop_node::calculate(std::stack<ptr<number_node>> &operands) {
  auto op2 = dynamic_cast<float_node*>(operands.top().get())->value;
  operands.pop();
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




}