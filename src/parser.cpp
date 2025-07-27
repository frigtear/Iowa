#include "parser.h"
#include "token.h"
#include <vector>
#include "errors.h"

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
    return logic_or();
}

Expression* Parser::logic_or() {
    Expression* expr = logic_and();
    while (match({TokenType::Or})) {
        TokenType op = previous().get_type();
        Expression* right = logic_and();
        expr = new BinaryExpression(expr, op, right);
    }
    return expr;
}

Expression* Parser::logic_and() {
    Expression* expr = equality();
    while (match({TokenType::And})) {
        TokenType op = previous().get_type();
        Expression* right = equality();
        expr = new BinaryExpression(expr, op, right);
    }
    return expr;
}

Expression* Parser::equality() {
    Expression* expr = comparison();
    while (match({TokenType::EqualsEquals, TokenType::NotEqual})) {
        TokenType op = previous().get_type();
        Expression* right = comparison();
        expr = new BinaryExpression(expr, op, right); 
    }
    return expr;
}

Expression* Parser::comparison(){
    Expression* expr = term();
    while (match({TokenType::GreaterThan, TokenType::LessThan})) {
        TokenType op = previous().get_type();
        Expression* right = term();
        expr = new BinaryExpression(expr, op, right); 
    }
    return expr;
}

Expression* Parser::term(){
    Expression* expr = factor();
    while (match({TokenType::Plus, TokenType::Minus})){
        TokenType op = previous().get_type();
        Expression* right = factor();
        expr = new BinaryExpression(expr, op, right); 
    }
    return expr;
}


Expression* Parser::factor() {
    Expression* expr = primary();
    while (match({TokenType::Multiply, TokenType::Divide})) {
        TokenType op = previous().get_type();
        Expression* right = factor(); 
        if (!right) {
            throw std::runtime_error("Missing right-hand side of binary operator");
        }
        expr = new BinaryExpression(expr, op, right);
    }
    return expr;
}

Expression* Parser::primary() {
    if (match({TokenType::Number})) {
        return new Literal(previous().get_value(), TokenType::Number);
    }
    if (match({ TokenType::Boolean })) {
        return new Literal(previous().get_value(), TokenType::Boolean);
    }
    if (match ({TokenType::String })){
        return new Literal(previous().get_value(), TokenType::String);
    }
    if (match({TokenType::ParenthesisOpen})) {
        Expression* expr = expression();
        if (!match({TokenType::ParenthesisClose})) {
            throw std::runtime_error("Expected closing parenthesis.");
        }
        return expr;
    }
    throw std::runtime_error("Expressions must be wrapped in parenthesis");
}

Expression* Parser::parse(){
    return expression();
}


void Parser::print_ast(Expression* expr){
    if (auto binary = dynamic_cast<BinaryExpression*>(expr)) {
        std::cout << "(";
        print_ast(binary->left);
        std::cout << " " << Token::get_type_string(binary->op) << " ";
        print_ast(binary->right);
        std::cout << ")";
    }
    else if (auto identifier = dynamic_cast<Identifier*>(expr)){
        std::cout << identifier->name;
    }
    else if (auto literal = dynamic_cast<Literal*>(expr)){
        std::cout << literal->value;
    }
}



Parser::evaluation Parser::evaluate_literal(Literal* literal){

    if (!literal) {
        throw std::runtime_error("Null literal encountered");
    }

    std::string literal_value = literal->value;
    TokenType literal_type = literal->type;

    if (literal_type == TokenType::Number){
        if (literal_value.empty()) {
            throw std::runtime_error("Literal value is empty");
        }
        return std::stoi(literal_value);
    }
    else if (literal_type == TokenType::Boolean){
        if (literal_value == "true"){
            return true;
        }
        else if (literal_value == "false"){
            return false;
        }
        else{
            std::runtime_error("Unsupported boolean type"); // Should be impossible but just in case
        }
    }
    return literal_value;
}

Parser::evaluation Parser::evaluate_identifier(Identifier* identifier){
    throw std::runtime_error("Identifiers are not implemented yet"); 
}

Parser::evaluation Parser::evaluate_binary(BinaryExpression* binary) {
    evaluation left = evaluate_expression(binary->left);
    evaluation right = evaluate_expression(binary->right);
    TokenType op = binary->op;

    return std::visit([&op](auto&& l, auto&& r) -> Parser::evaluation {
        using L = std::decay_t<decltype(l)>;
        using R = std::decay_t<decltype(r)>;

        if constexpr (std::is_same_v<L, int> && std::is_same_v<R, int>) {
            switch (op) {
                case TokenType::Plus:      return l + r;
                case TokenType::Minus:     return l - r;
                case TokenType::Multiply:  return l * r;
                case TokenType::Divide:
                    if (r == 0) throw std::runtime_error("Division by zero");
                    return l / r;
                default:
                    throw std::runtime_error("Unsupported integer operation");
            }
        }
        else if constexpr (std::is_same_v<L, bool> && std::is_same_v<R, bool>){
            switch(op){
                case TokenType::And: return l && r;
                case TokenType::Or: return l || r;
                default:
                    throw std::runtime_error("Unsuported boolean operation");
            }
        }
        else {
            throw std::runtime_error("Unsupported operand types for binary expression");
        }
    }, left, right);
}


Parser::evaluation Parser::evaluate_expression(Expression* expr){
    if (!expr) {
        throw std::runtime_error("Null expression encountered during evaluation");
    }
    else if (auto binary = dynamic_cast<BinaryExpression*>(expr)){
        return evaluate_binary(binary);
    }
    else if (auto identifier = dynamic_cast<Identifier*>(expr)){
        return evaluate_identifier(identifier);
    }
    else if (auto literal = dynamic_cast<Literal*>(expr)){
        return evaluate_literal(literal);
    }
}



