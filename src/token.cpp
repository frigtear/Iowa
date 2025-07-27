#include "token.h"
#include <stdio.h>

Token::Token(std::string val, TokenType t){
    value = val;
    type = t;
}

std::string Token::get_value() const {
    return value;
}

TokenType Token::get_type() const {
    return type;
}

std::string Token::get_type_string() const{
    switch (type) {
        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Multiply: return "Multiply";
        case TokenType::Divide: return "Divide";
        case TokenType::Equals: return "Equals";
        case TokenType::EqualsEquals: return "EqualsEquals";
        case TokenType::NotEqual: return "NotEqual";
        case TokenType::GreaterThan: return "GreaterThan";
        case TokenType::LessThan: return "LessThan";
        case TokenType::Semicolon: return "Semicolon";
        case TokenType::ParenthesisOpen: return "ParenthesisOpen";
        case TokenType::ParenthesisClose: return "ParenthesisClose";
        case TokenType::BracketOpen: return "BracketOpen";
        case TokenType::BracketClose: return "BracketClose";
        case TokenType::If: return "If";
        case TokenType::Else: return "Else";
        case TokenType::Say: return "Say";
        case TokenType::String: return "String";
        case TokenType::Number: return "Number";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Eof: return "EOF";
        default: return "Unknown";
    }
}