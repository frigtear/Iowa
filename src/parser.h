#ifndef PARSER_H
#define PARESER_H

#include "expressions.h"
#include <vector>

class Parser{
    public:
        std::vector<Lexeme>* tokens;
        int current = 0;
        Parser(std::vector<Lexeme>* t) : tokens(t) {}

    private: 
        bool match()
};

#endif 