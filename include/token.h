#ifndef __token_h__
#define __token_h__
#include <vector>
#include <memory>
#include <stack>
#include <cmath>

#ifdef debug
#include <iostream>
#endif

#define round(r) ( r > 0.0) ? (int)( r +0.5) : (int)( r -0.5)

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
  virtual void calculate(std::stack<ptr<token_node>> &operands) = 0;
  // 给定栈顶和拿到的操作符，判断是否应该pop
  bool should_pop(token_node* top, token_node* next);

};
struct operator_node : token_node {
  void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands);
  virtual void calculate(std::stack<ptr<token_node>> &operands) = 0;
};
struct number_node : token_node {
  void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands);
  void calculate(std::stack<ptr<token_node>> &operands) {}
};
// struct integer_node : number_node {
//   long long value;
// };
struct float_node : number_node {
  double value;
};
struct binop_node : operator_node {
  bin_op op;
  void calculate(std::stack<ptr<token_node>> &operands);
};
struct unaryop_node : operator_node {
  unary_op op;
  void calculate(std::stack<ptr<token_node>> &operands);
};
struct leftparen_node : operator_node {
  void calculate(std::stack<ptr<token_node>> &operands) {};
};
struct rightparen_node : operator_node {
  void calculate(std::stack<ptr<token_node>> &operands) {exit(1);}
  void processor(std::stack<ptr<token_node>> &operators, std::stack<ptr<token_node>> &operands) override;
};
struct end_node : operator_node {
  void calculate(std::stack<ptr<token_node>> &operands) {exit(1);};

};

void insert(std::vector<token_list::token_node*> &list, double n);
void insert(std::vector<token_list::token_node*> &list, token_list::bin_op op);
void insert(std::vector<token_list::token_node*> &list, token_list::unary_op op);

class List {
    public:
    std::stack<ptr<token_node>> operators, operands;
    std::vector<token_list::token_node*> list_;
    friend List& operator<<(List& me, double n);
    friend List& operator<<(List& me, int n);
    friend List& operator<<(List& me, std::string s);
    void getString(std::string str);
    double calculate();
};

}

#endif
