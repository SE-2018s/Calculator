#include "syntax_tree.h"
namespace syntax_tree{
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
      return int(left->calculate()) % int(right->calculate());
      break;
    case bin_op::exponentiation :
      return powl(left->calculate(), right->calculate());
      break; 
    default: 
      //
  }
}
}