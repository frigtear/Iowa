#ifndef LEXEMES_H
#define LEXEMES_H

#include <iostream>

enum class TokenType{
    // Operators,
    Plus,
    Minus,
    Multiply,
    Divide,
    Or,
    And,
    Equals,
    EqualsEquals,
    NotEqual,
    GreaterThan,
    LessThan,

    Type,

    Semicolon,
    ParenthesisOpen,
    ParenthesisClose,
    BracketOpen,
    BracketClose,
    
    If,
    Else,
    Say,
    Set,

    String,
    Number,
    Boolean,

    Identifier,

    Eof,
};

class Token{
    public:
        Token(std::string val, TokenType type);
        std::string get_value() const;
        TokenType get_type() const;
        static std::string get_type_string(TokenType type);

    private:
        std::string value;
        TokenType type; 
};

#endif 