#include "parser.h"
#include "lexemes.h"
#include <vector>

Lexeme Parser::peek(){
    return tokens->at(current);
}

Lexeme Parser::previous(){
    current --;
    return peek();
}

Lexeme Parser::next(){
    current ++;
    return peek();
}

bool Parser::match(std::vector<TokenType> type){
    Lexeme current_value = peek();
    current += 1;
    TokenType current_type = current_value.get_type();
    return (current_type == type);
}


Expression Parser::expression(){
    return equality();
}

Expression Parser::equality(){
    while match()
}