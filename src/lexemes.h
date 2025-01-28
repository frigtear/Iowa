#ifndef LEXEMES_H
#define LEXEMES_H

#include <iostream>

enum class TokenType{
    Operator,
    Bracket_Open,
    Bracket_Close,
    String_Literal,
    Digit,
    Identifier,
    Assignment,
};
/*
If,
    Else,
    Iterate_through,
    With,
    While, 
    Condition,
    Integer,
    String,
};
*/

class Lexeme{
    public:
        Lexeme(std::string val, TokenType type);
        std::string get_value() const;
        TokenType get_type() const;

    private:
        std::string value;
        TokenType type; 
};

#endif 