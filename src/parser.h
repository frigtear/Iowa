#ifndef PARSER_H
#define PARSER_H

#include "expressions.h"
#include <vector>

class Parser{
    public:
        Parser(std::vector<Lexeme>* t) : tokens(t) {}

        Lexeme peek();
        Lexeme previous();
        Lexeme advance();
        Lexeme next();
        bool match(std::vector<Lexeme> tokens);
        
        Expression expression();
        Expression equality();


    private: 
        std::vector<Lexeme>* tokens;
        int current = 0;

        
};

#endif 