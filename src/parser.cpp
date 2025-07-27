#include "parser.h"
#include "token.h"
#include <vector>

Token Parser::peek() {
    return tokens.at(current);
}

Token Parser::previous() {
    if (current > 0){
        return tokens.at(current - 1);
    }
    return Token("", TokenType::Eof);
}

Token Parser::next() {
    if (current < number_of_tokens - 1){
        current++;
        return peek();
    }
    return Token("", TokenType::Eof);
}

Parser::Parser(std::vector<Token> t) : tokens(t), current(0)
{
    number_of_tokens = t.size();
}

bool Parser::match(std::vector<TokenType> types){
    for (auto type : types){
        if (peek().get_type() == type){
            next();
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
        expr = new BinaryExpression(expr, op, right); 
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
        }
        return expr;
    }
 
    return nullptr;
}


Expression* Parser::parse(){
    return expression();
}

void Parser::print_ast(Expression* expr){
    if (auto binary = dynamic_cast<BinaryExpression*>(expr)) {
        print_ast(binary->left);
        std::cout << binary->op << " ";
        print_ast(binary->right);

    }
    else if (auto identifier = dynamic_cast<Identifier*>(expr)){
        std::cout << identifier->name << " ";
    }
    else if (auto literal = dynamic_cast<Literal*>(expr)){
        std::cout << literal->value << " ";
    }
}

