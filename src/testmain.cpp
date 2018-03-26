#include "token.h"
#include <iostream>
#include <string>
void insert(std::vector<token_list::token_node*> &list, double n) {
    auto node = new token_list::float_node;
    node->value = n;
    list.push_back(node);
}
void insert(std::vector<token_list::token_node*> &list, token_list::bin_op op) {
    auto node = new token_list::binop_node;
    node->op = op;
    list.push_back(node);
    // switch(op) {
    //     case token_list::plus :
    //     case token_list::minus :
    //         auto node = new token_list::binop_node;
    //         node->op = op;
    //         list.push_back(node);
    //     case token_list::bin_op::
    // }
}
void insert(std::vector<token_list::token_node*> &list, token_list::unary_op op) {
    auto node = new token_list::unaryop_node;
    node->op = op;
    list.push_back(node);
}
class List {
    public:
    std::vector<token_list::token_node*> list_;
    friend List& operator<<(List& me, token_list::unary_op op) {
        insert(me.list_, op);
        return me;
    }
    friend List& operator<<(List& me, token_list::bin_op op) {
        insert(me.list_, op);
        return me;
    }
    friend List& operator<<(List& me, double n) {
        insert(me.list_, n);
        return me;
    }
    friend List& operator<<(List& me, int n) {
        insert(me.list_, (double)n);
        return me;
    }
    friend List& operator<<(List& me, std::string s) {
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
};
int main() {
    std::stack<std::shared_ptr<token_list::token_node>> operators, operands;
    List list;

    list << 1.0 << "*" << 3 << "^" << 5 << "*" << "cos" << "sin" << 2 << "*" << 1 << "^" << 2 << "^" << 2 << ")" << "-" << "ln" << 1 << "*" << 2 << ")" << "-" << 3 << "-" << 5 << "end";

    // token_list::float_node* n;
    // token_list::binop_node* o;
    // token_list::unaryop_node* u;
    // token_list::rightparen_node* r;

    // n = new token_list::float_node;
    // n->value = 1;
    // list.push_back(n);

    // o = new token_list::binop_node;
    // o->op = token_list::bin_op::plus;
    // list.push_back(o);

    // u = new token_list::unaryop_node;
    // u->op = token_list::unary_op::cos;
    // list.push_back(u);

    // n = new token_list::float_node;
    // n->value = 3.1415926;
    // list.push_back(n);

    // r = new token_list::rightparen_node;
    // list.push_back(r);

    // o = new token_list::binop_node;
    // o->op = token_list::bin_op::multiply;
    // list.push_back(o);

    // n = new token_list::float_node;
    // n->value = 4;
    // list.push_back(n);

    // int count = 0;

    for (auto t : list.list_) {
        // if (dynamic_cast<token_list::float_node*>(t)) {
        //     std::cout << dynamic_cast<token_list::float_node*>(t)->value;
        // } else {
        //     std::cout << dynamic_cast<token_list::binop_node*>(t)->op;
        // }
        // std::cerr << "main : processing " << count ++ << std::endl;
        t->processor(operators, operands);
    }
    // auto end = new token_list::end_node;
    // end->processor(operators, operands);
    std::cout << dynamic_cast<token_list::float_node*>(operands.top().get())->value;
}