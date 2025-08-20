#include "token.h"

Token::Token() {}

Token::Token(std::string val, TokenType t) {
    value = val;
    type = t;
}

std::string Token::get_value() const {
    return value;
}

TokenType Token::get_type() const {
    return type;
}

std::string Token::get_type_string(TokenType type) {
    switch (type) {
        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Multiply: return "Multiply";
        case TokenType::Divide: return "Divide";
        case TokenType::Or: return "Or";
        case TokenType::And: return "And";
        case TokenType::Equals: return "Equals";
        case TokenType::EqualsEquals: return "EqualsEquals";
        case TokenType::NotEqual: return "NotEqual";
        case TokenType::GreaterThan: return "GreaterThan";
        case TokenType::GreaterEqualsThan: return "GreaterEqualsThan";
        case TokenType::LessThan: return "LessThan";
        case TokenType::LessEqualsThan: return "LessEqualsThan";
        case TokenType::Semicolon: return "Semicolon";
        case TokenType::ParenthesisOpen: return "ParenthesisOpen";
        case TokenType::ParenthesisClose: return "ParenthesisClose";
        case TokenType::BracketOpen: return "BracketOpen";
        case TokenType::BracketClose: return "BracketClose";
        case TokenType::If: return "If";
        case TokenType::Else: return "Else";
        case TokenType::Loop: return "Loop";
        case TokenType::ConsoleOut: return "Console_out";
        case TokenType::Set: return "Set";
        case TokenType::String: return "String";
        case TokenType::Number: return "Number";
        case TokenType::Boolean: return "Boolean"; 
        case TokenType::Identifier: return "Identifier";
        case TokenType::Function: return "Function";
        case TokenType::Eof: return "EOF";
        default: return "Unknown";
    }
}
