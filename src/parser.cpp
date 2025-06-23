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

Expression Parser::expression() {
    return equality();
}

Expression Parser::equality() {
    Expression* expr = comparison(); // You need to implement comparison()
    while (match({"==", "!="})) {
        std::string op = previous().get_value();
        Expression* right = comparison();
        expr = BinaryExpression(expr, op, right); // Adjust to your AST node constructor
    }
    return expr;
}


Expression Parser::comparison(){
    Expression* expr = term(); // You need to implement comparison()
    while (match({">", "<", ">=", "<="})) {
        std::string op = previous().get_value();
        Expression* right = term();
        expr = BinaryExpression(expr, op, right); // Adjust to your AST node constructor
    }
    return expr;
}