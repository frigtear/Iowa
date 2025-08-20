#ifndef LEXEMES_H
#define LEXEMES_H

#include <iostream>

enum class TokenType {

    // Operators
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
    GreaterEqualsThan,
    LessThan,
    LessEqualsThan,

    // Keywords
    If,
    Else,
    ConsoleOut,
    Set,
    Loop,
    Function,

    // Symbols
    Semicolon,
    ParenthesisOpen,
    ParenthesisClose,
    BracketOpen,
    BracketClose,

    // Literals
    String,
    Number,
    Boolean,

    Identifier,
    Eof
};

class Token {
public:
    Token();
    Token(std::string val, TokenType type);
    std::string get_value() const;
    TokenType get_type() const;
    static std::string get_type_string(TokenType type);

private:
    std::string value;
    TokenType type;
};

#endif 
