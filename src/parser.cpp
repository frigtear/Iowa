#include "parser.h"
#include "token.h"
#include <vector>

Token Parser::peek() {
    return tokens->at(current);
}

Token Parser::previous() {
    return tokens->at(current - 1);
}

Token  Parser::next() {
    current++;
    return peek();
}


bool Parser::match(std::vector<TokenType> types){
    for (auto type : types){
        if (peek().get_type() == type){
            current++;
            return true;
        }
    }
    return false;
}

Expression* Parser::expression() {
    return equality();
}

Expression* Parser::equality() {
    Expression* expr = comparison();
    while (match({TokenType::EqualsEquals, TokenType::NotEqual})) {
        std::string op = previous().get_value();
        Expression* right = comparison();
        expr = new BinaryExpression(expr, op, right); // Fixed: don't redeclare expr
    }
    return expr;
}

Expression* Parser::comparison(){
    Expression* expr = term();
    while (match({TokenType::GreaterThan, TokenType::LessThan})) {
        std::string op = previous().get_value();
        Expression* right = term();
        expr = new BinaryExpression(expr, op, right); // Fixed: don't redeclare expr
    }
    return expr;
}

Expression* Parser::term(){
    Expression* expr = factor();
    while (match({TokenType::Plus, TokenType::Minus})){
        std::string op = previous().get_value();
        Expression* right = factor();
        expr = new BinaryExpression(expr, op, right); // Fixed: don't redeclare expr
    }
    return expr;
}

Expression* Parser::factor(){
    Expression* expr = primary();
    while (match({TokenType::Multiply, TokenType::Divide})){
        std::string op = previous().get_value();
        Expression* right = primary();
        expr = new BinaryExpression(expr, op, right); // Fixed: don't redeclare expr
    }
    return expr;
}

Expression* Parser::primary() {
    if (match({TokenType::Identifier})) {
        return new Identifier(previous().get_value());
    }
    if (match({TokenType::Number, TokenType::String})) {
        return new Literal(previous().get_value());
    }
    if (match({TokenType::ParenthesisOpen})) {
        Expression* expr = expression();
        if (!match({TokenType::ParenthesisClose})) {
            // Handle error: expected ')'
        }
        return expr;
    }
    // Handle error: expected expression
    return nullptr;
}