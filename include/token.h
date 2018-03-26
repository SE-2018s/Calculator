#include <vector>
#include <memory>
#include <stack>
#include <cmath>

#include <iostream>

// using syn_tree = std::shared_ptr<syntax_tree::syntax_node>;
namespace token_list {

template <typename T>
using ptr = std::shared_ptr<T>;

enum unary_op {
  positive,
  negative,
  sin,
  cos,
  tan,
  sqrt,
  factorial,
  logarithm
};
enum bin_op {
  plus,
  minus,
  multiply,
  divide,
  modulo,
  exponentiation
};


struct token_node {
  virtual void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) = 0;
  virtual ptr<token_node> calculate(std::stack<ptr<token_node>> &operands) = 0;
  // 给定栈顶和拿到的操作符，判断是否应该pop
  bool should_pop(token_node* top, token_node* next);

};
struct operator_node : token_node {
  void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands);
  virtual ptr<token_node> calculate(std::stack<ptr<token_node>> &operands) = 0;
};
struct number_node : token_node {
  void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands);
  ptr<token_node> calculate(std::stack<ptr<token_node>> &operands) {}
};
// struct integer_node : number_node {
//   long long value;
// };
struct float_node : number_node {
  double value;
};
struct binop_node : operator_node {
  bin_op op;
  ptr<token_node> calculate(std::stack<ptr<token_node>> &operands);
};
struct unaryop_node : operator_node {
  unary_op op;
  ptr<token_node> calculate(std::stack<ptr<token_node>> &operands);
};
struct leftparen_node : operator_node {
  ptr<token_node> calculate(std::stack<ptr<token_node>> &operands) {ptr<token_node> p(nullptr); return p;};
};
struct rightparen_node : operator_node {
  void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) override;
};
struct end_node : operator_node {
  ptr<token_node> calculate(std::stack<ptr<token_node>> &operands) {ptr<token_node> p(nullptr); return p;};

};
}