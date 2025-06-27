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
        bool match(std::vector<TokenType> types);    

        Expression* expression();
        Expression* equality();
        Expression* comparison();
        Expression* term();
        Expression* primary();
        Expression* factor();
        Expression* primary();
        Expression* assignment();
        Expression* expression_statement();
        Expression* if_statement();
        Expression* literal();
        Expression* identifier();
        Expression* number();
        Expression* string_literal(); 
        Expression* equality_operator();
        Expression* comparison_operator();
        

    private: 
        std::vector<Lexeme>* tokens;
        int current = 0;
};

#endif