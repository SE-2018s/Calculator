#include <memory>
#include <cmath>
namespace syntax_tree{

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
struct syntax_node {
  virtual double calculate();
};

struct number_node : syntax_node {
  virtual double calculate();
};

struct intenger_node: number_node {
  int value;
  virtual double calculate();
};
struct float_node : number_node {
  double value;
  virtual double calculate();
};
struct bin_op_node : syntax_node {
  bin_op op;
  std::shared_ptr<number_node> left, right;
  virtual double calculate();
};
struct unary_op_node : syntax_node {
  unary_op op;
  std::shared_ptr<number_node> child;
  virtual double calculate();
};
}