#include "lexemes.h"
#include <stdio.h>

Lexeme::Lexeme(std::string val, TokenType type){
    value = val;
}

std::string Lexeme::get_value() const {
    return value;
}

TokenType Lexeme::get_type() const {
    return type;
}




