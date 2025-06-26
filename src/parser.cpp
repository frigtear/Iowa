#include "parser.h"
#include "lexemes.h"
#include <vector>

Lexeme Parser::peek() {
    return tokens->at(current);
}

Lexeme Parser::previous() {
    return tokens->at(current - 1);
}

Lexeme Parser::next() {
    current++;
    return peek();
}

bool Parser::match(std::vector<std::string> types) {
    for (auto type : types) {
        if (peek().get_value() == type) {
            current++;
            return true;
        }
    }
    return false;
}


bool Parser::match(std::vector<TokenType> typesg){
    for (auto type : types){
        if (peek().get_type() == type){
            current++;
            return true;
        }
    }
}

Expression* Parser::expression() {
    return equality();
}

Expression* Parser::equality() {
    Expression* expr = comparison();
    while (match({"==", "!="})) {
        std::string op = previous().get_value();
        Expression* right = comparison();
        Expression* expr = new BinaryExpression(expr, op, right); // Allocate on heap and assign to expr
    }
    return expr;
}

Expression* Parser::comparison(){
    Expression* expr = term(); // You need to implement comparison()
    while (match({">", "<", ">=", "<="})) {
        std::string op = previous().get_value();
        Expression* right = term();
        Expression* expr = new BinaryExpression(expr, op, right); // Adjust to your AST node constructor
    }
    return expr;
}

Expression* Parser::term(){
    Expression* expr = factor();
    while (match({"+", "-"})){
        std::string op = previous().get_value();
        Expression* right = factor();
        Expression* expr = new BinaryExpression(expr, op, right);
    }
    return expr;
}

Expression* Parser::factor(){
    Expression* expr = primary();
    while (match({"*", "/"})){
        std::string op = previous().get_value();
        Expression* right = primary();
        Expression* expr = new BinaryExpression(expr, op, right);
    }
    return expr;
}

Expression* Parser::primary() {
    if (match({TokenType::Identifier})) {
        return new Identifier(previous().get_value());
    }
    if (match({TokenType::Digit, TokenType::String_Literal})) {
        return new Literal(previous().get_value());
    }
    if (match({TokenType::Bracket_Open})) {
        Expression* expr = expression();
        if (!match({TokenType::Bracket_Close})) {
            // Handle error: expected ')'
        }
        return expr;

    }
    // Handle error: expected expression
    return nullptr;
}
