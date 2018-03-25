#include <vector>
#include "syntax_tree.h"
#include <stack>

template <typename T>
using ptr = std::shared_ptr<T>;

using syn_tree = std::shared_ptr<syntax_tree::syntax_node>;
namespace token_list {

enum unary_op {
  plus = 0,
  minus,
  sin,
  cos,
  tan,
  sqrt,
  factorial,
  logarithm
};
enum bin_op {
  plus = 0,
  minus,
  multiply,
  divide,
  modulo,
  exponentiation
};


struct token_node {
  virtual void processor(std::stack<ptr<operator_node>> &operators, std::stack<ptr<number_node>> &operands) = 0;
  virtual ptr<number_node> calculate(std::stack<ptr<number_node>> &operands);
  // 给定栈顶和拿到的操作符，判断是否应该pop
  bool should_pop(operator_node* top, operator_node* next);

};
struct operator_node : token_node {
  void processor(std::stack<ptr<operator_node>> &operators, std::stack<ptr<number_node>> &operands);
  virtual ptr<number_node> calculate(std::stack<ptr<number_node>> &operands);
};
struct number_node : token_node {
  void processor(std::stack<ptr<operator_node>> &operators, std::stack<ptr<number_node>> &operands);
};
// struct integer_node : number_node {
//   long long value;
// };
struct float_node : number_node {
  double value;
};
struct binop_node : operator_node {
  bin_op op;
  ptr<number_node> calculate(std::stack<ptr<number_node>> &operands);
};
struct unaryop_node : operator_node {
  unary_op op;
  ptr<number_node> calculate(std::stack<ptr<number_node>> &operands);
};
struct leftparen_node : operator_node {
  unary_op op;
  ptr<number_node> calculate(std::stack<ptr<number_node>> &operands);
};
struct rightparen_node : operator_node {
  unary_op op;
};
}