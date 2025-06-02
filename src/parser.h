#ifndef PARSER_H
#define PARESER_H

#include "expressions.h"
#include <vector>

class Parser{
    public:
        std::vector<Lexeme>* tokens;
        
        Parser(std::vector<Lexeme>* t) : tokens(t) {}

    private:

};

#endif