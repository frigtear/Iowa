#include "lexemes.h"
#include <stdio.h>

Lexeme::Lexeme(std::string val, TokenType t){
    value = val;
    type = t;
}

std::string Lexeme::get_value() const {
    return value;
}

TokenType Lexeme::get_type() const {
    return type;
}

std::string Lexeme::get_type_string() const{
    switch (type) {
        case TokenType::Operator: return "Operator";
        case TokenType::Bracket_Open: return "Bracket_Open";
        case TokenType::Bracket_Close: return "Bracket_Close";
        case TokenType::String_Literal: return "String_Literal";
        case TokenType::Digit: return "Digit";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Assignment: return "Assignment";
        default: return "Unknown";
    }
}