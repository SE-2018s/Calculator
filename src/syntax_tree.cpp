#include "./include/syntax_tree.h"

#define round(r) \
  (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5)

namespace syntax_tree{

// 单目运算符：+ - sin cos tan 平方根 阶乘 对数
double unary_op_node::calculate() {
  switch(op){
    case unary_op::plus :
      return child->calculate();
      break;
    case unary_op::minus :
      return -child->calculate();
      break;
    case unary_op::sin :
      return sin(child->calculate());
      break;
    case unary_op::cos :
      return cos(child->calculate());
      break;
    case unary_op::tan :
      return tan(child->calculate());
      break;
    case unary_op::sqrt :
      return sqrt(child->calculate());
      break;
    case unary_op::factorial :
      int n = round(child->calculate());
      int result = 1;
      while(n >= 1){
        result *= n;
        n--;
      }
      return result;
      break;
    case unary_op::logarithm :
      return log(child->calculate());
      break;
    default:
      //
  }
}

// 双目运算符：+ - * /  % ^
double bin_op_node::calculate() {
  switch(op){
    case bin_op::plus : 
      return left->calculate() + right->calculate(); 
      break;
    case bin_op::minus : 
      return left->calculate() - right->calculate(); 
      break;
    case bin_op::multiply : 
      return left->calculate() * right->calculate(); 
      break;
    case bin_op::divide : 
      return left->calculate() / right->calculate(); 
      break;
    case bin_op::modulo : 
      return int(round(left->calculate())) % int(round(right->calculate()));
      break;
    case bin_op::exponentiation :
      return powl(left->calculate(), right->calculate());
      break; 
    default: 
      //
  }
}

double factorial(double n){
  if(n <= 0) 
    return 1;
  else 
    return factorial(n - 1) * n;
}
}
