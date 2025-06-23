#ifndef PARSER_H
#define PARSER_H

#include "expressions.h"
#include <vector>

class Parser{
    public:
        Parser(std::vector<Lexeme>* t) : tokens(t) {}

        Lexeme peek();
        Lexeme previous();
        Lexeme next();
        bool match(std::vector<std::string> types);
       // bool match(std::vector<std::string> strings);
        Expression expression();
        Expression equality();
        Expression comparison();
        Expression term();

    private: 
        std::vector<Lexeme>* tokens;
        int current = 0;
};

#endif