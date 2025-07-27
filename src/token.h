#ifndef LEXEMES_H
#define LEXEMES_H

#include <iostream>

enum class TokenType{
    // Operators,
    Plus,
    Minus,
    Multiply,
    Divide,
    Equals,
    EqualsEquals,
    NotEqual,
    GreaterThan,
    LessThan,

    Semicolon,
    ParenthesisOpen,
    ParenthesisClose,
    BracketOpen,
    BracketClose,
    
    If,
    Else,
    Say,

    String,
    Number,

    Identifier,

    Eof,
};

class Token{
    public:
        Token(std::string val, TokenType type);
        std::string get_value() const;
        TokenType get_type() const;
        std::string get_type_string() const;

    private:
        std::string value;
        TokenType type; 
};

#endif 