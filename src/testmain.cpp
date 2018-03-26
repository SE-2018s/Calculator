#include "token.h"
#include <iostream>
int main() {
    std::stack<std::shared_ptr<token_list::token_node>> operators, operands;
    std::vector<token_list::token_node*> list;

    token_list::float_node* n;
    token_list::binop_node* o;

    n = new token_list::float_node;
    n->value = 1;
    list.push_back(n);

    o = new token_list::binop_node;
    o->op = token_list::bin_op::plus;
    list.push_back(o);

    n = new token_list::float_node;
    n->value = 65536;
    list.push_back(n);

    // o = new token_list::binop_node;
    // o->op = token_list::bin_op::multiply;
    // list.push_back(o);

    // n = new token_list::float_node;
    // n->value = 4;
    // list.push_back(n);

    int count = 0;

    for (auto t : list) {
        // if (dynamic_cast<token_list::float_node*>(t)) {
        //     std::cout << dynamic_cast<token_list::float_node*>(t)->value;
        // } else {
        //     std::cout << dynamic_cast<token_list::binop_node*>(t)->op;
        // }
        std::cerr << "main : processing " << count ++ << std::endl;
        t->processor(operators, operands);
    }
    auto end = new token_list::end_node;
    end->processor(operators, operands);
    std::cout << dynamic_cast<token_list::float_node*>(operands.top().get())->value;
}