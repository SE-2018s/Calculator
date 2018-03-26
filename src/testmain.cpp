#include "token.h"
#include <iostream>
#include <string>

int main() {
    {
        token_list::List list;

        list << 1.0 << "*" << 3 << "^" << 5 << "*" << "cos" << "sin" << 2 << "*" << 1 << "^" << 2 << "^" << 2 << ")" << "-" << "ln" << 1 << "*" << 2 << ")" << "-" << 3 << "-" << 5 << "end";
        try {
            double rst = list.calculate();
            std::cout << rst << std::endl;
        }
        catch (const char* errmsg) {
            std::cerr << errmsg;
        }
    }
    {
        token_list::List list;
    
        list << 1 << 3 << "^" << 5 << "*" << "cos" << "sin" << 2 << "*" << 1 << "^" << 2 << "^" << 2 << ")" << "-" << "ln" << 1 << "*" << 2 << ")" << "-" << 3 << "-" << 5 << "end";
        try {
            double rst = list.calculate();
            std::cout << rst << std::endl;
        }
        catch (const char* errmsg) {
            std::cerr << errmsg;
        }
    }
}