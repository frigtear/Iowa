#include "parser.h"
#include "token.h"
#include <vector>
#include <memory>
#include "errors.h"

Token Parser::peek() const {
    return tokens.at(current);
}

Token Parser::previous() {
    if (current > 0) {
        return tokens.at(current - 1);
    }
    return Token("", TokenType::Eof);
}

Token Parser::consume(TokenType expected, const std::string& errorMessage) {
    if (peek().get_type() == expected) {
        Token temp = peek();
        next();
        return temp;
    }

    throw std::runtime_error(errorMessage + " Got “" + Token::get_type_string(peek().get_type()) + "”.");
}


Token Parser::next() {
    if (current < number_of_tokens - 1) {
        current++;
        return peek();
    }
    return Token("", TokenType::Eof);
}

bool Parser::is_at_end() {
    return (peek().get_type() == TokenType::Eof);
}

bool Parser::check(TokenType type) const {
    return (peek().get_type() == type);
}

Parser::Parser(std::vector<Token> t) : tokens(t), current(0) {
    number_of_tokens = t.size();
}

bool Parser::match_impl(std::vector<TokenType>& types, Token* out){
    for (auto type : types) {
        if (peek().get_type() == type) {

            if (out != nullptr){
                Token token = peek();
                *out = token;
            }
            next();

            return true;
        }
    }
    return false;
}

bool Parser::match(std::vector<TokenType> types) {
    return match_impl(types, nullptr);
}

bool Parser::match(std::vector<TokenType> types, Token& matched_token) {
    bool result = match_impl(types, &matched_token);
    return result;
}

std::unique_ptr<Declaration> Parser::program() {
    std::vector<std::unique_ptr<Declaration>> declarations;
    while (!is_at_end()) {
        declarations.push_back(declaration());
    }
    return std::make_unique<Program>(std::move(declarations));
}

std::unique_ptr<Declaration> Parser::declaration() {
    if (match({TokenType::Set})) {
        return dynamic_declaration();
    } else {
        return statement();
    }
}

std::unique_ptr<Declaration> Parser::dynamic_declaration() {
    Token nameToken = consume(TokenType::Identifier, "Expected identifier after 'set'.");
    std::string variable_name = nameToken.get_value();
    consume(TokenType::Equals, "Expected '=' after variable name.");
    auto variable_value = expression();
    consume(TokenType::Semicolon, "Expected ';' after variable declaration.");
    return std::make_unique<DynamicDeclaration>(std::move(variable_name), std::move(variable_value));
}

std::unique_ptr<Declaration> Parser::statement() {
    if (match({TokenType::ConsoleOut})) {
        return print_statement();
    } else if (match({TokenType::BracketOpen})) {
        return block();
    } else if (match({TokenType::If})) {
        return if_statement();
    } else if (match({TokenType::Loop})){
        return loop_statement();
    } else {
        return expression_statement();
    }
}

std::unique_ptr<Statement> Parser::block() {
    std::vector<std::unique_ptr<Declaration>> statements;
    while (!(peek().get_type() == TokenType::BracketClose) && !is_at_end()) {
        statements.push_back(declaration());
    }
    consume(TokenType::BracketClose, "Expect '}' after block.");
    return std::make_unique<Block>(std::move(statements));
}

std::unique_ptr<Statement> Parser::expression_statement() {
    auto value = expression();
    consume(TokenType::Semicolon, "Expect ';' after value.");
    return std::make_unique<ExpressionStatement>(std::move(value));
}

std::unique_ptr<Statement> Parser::if_statement() {
    consume(TokenType::ParenthesisOpen, "Expected '(' after 'if'.");
    auto condition = expression();
    consume(TokenType::ParenthesisClose, "Expected ')' after condition.");

    consume(TokenType::BracketOpen, "Expected '{' to start 'if' block.");
    auto thenBlock = std::unique_ptr<Block>(dynamic_cast<Block*>(block().release()));
    if (!thenBlock) {
        throw std::runtime_error("If branch must be a block.");
    }

    std::unique_ptr<Block> elseBlock = nullptr;
    if (match({TokenType::Else})) {
        consume(TokenType::BracketOpen, "Expected '{' to start 'else' block.");
        elseBlock = std::unique_ptr<Block>(dynamic_cast<Block*>(block().release()));
        if (!elseBlock) {
            throw std::runtime_error("Else branch must be a block.");
        }
    }

    return std::make_unique<IfStatement>(std::move(condition), std::move(thenBlock), std::move(elseBlock));
}

std::unique_ptr<Statement> Parser::loop_statement() {
    consume(TokenType::ParenthesisOpen, "Expected '(' after 'loop'.");
    auto condition = expression();
    consume(TokenType::ParenthesisClose, "Expected ')' after condition.");
    consume(TokenType::BracketOpen, "Expected '{' to start 'loop' block.");
    auto loop_block = std::unique_ptr<Block>(dynamic_cast<Block*>(block().release()));

    return std::make_unique<LoopStatement>(std::move(condition), std::move(loop_block));
}

std::unique_ptr<Statement> Parser::print_statement() {
    auto value = expression();
    consume(TokenType::Semicolon, "Expect ';' after value.");
    return std::make_unique<PrintStatement>(std::move(value));
}

std::unique_ptr<Expression> Parser::expression() {
    return logic_or();
}

std::unique_ptr<Expression> Parser::logic_or() {
    auto expr = logic_and();
    while (match({TokenType::Or})) {
        TokenType op = previous().get_type();
        auto right = logic_and();
        expr = std::make_unique<BinaryExpression>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::logic_and() {
    auto expr = equality();
    while (match({TokenType::And})) {
        TokenType op = previous().get_type();
        auto right = equality();
        expr = std::make_unique<BinaryExpression>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::equality() {
    auto expr = comparison();
    while (match({TokenType::EqualsEquals, TokenType::NotEqual})) {
        TokenType op = previous().get_type();
        auto right = comparison();
        expr = std::make_unique<BinaryExpression>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::comparison() {
    auto expr = term();
    while (match({TokenType::GreaterThan, TokenType::LessThan, TokenType::GreaterEqualsThan, TokenType:: LessEqualsThan})) {
        TokenType op = previous().get_type();
        auto right = term();
        expr = std::make_unique<BinaryExpression>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::term() {
    auto expr = factor();
    while (match({TokenType::Plus, TokenType::Minus})) {
        TokenType op = previous().get_type();
        auto right = factor();
        expr = std::make_unique<BinaryExpression>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::factor() {
    auto expr = call();
    while (match({TokenType::Multiply, TokenType::Divide})) {
        TokenType op = previous().get_type();
        auto right = factor();
        if (!right) {
            throw std::runtime_error("Missing right-hand side of binary operator");
        }
        expr = std::make_unique<BinaryExpression>(std::move(expr), op, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::call(){
    auto expr = primary();
    while (match({TokenType::ParenthesisOpen})){
        auto args = arguments();
        consume(TokenType::ParenthesisClose, "Expected ) after arguments");
        expr = std::make_unique<Call>(std::move(expr), std::move(args));
    }
    return expr;
}

std::unique_ptr<Arguments> Parser::arguments(){
    std::vector<std::unique_ptr<Expression>> args;
    while (match({TokenType::Identifier})){
        consume(TokenType::Equals, "Expected '=' after identifier");
        args.push_back(expression());
    }
    std::unique_ptr<Arguments> arguments = std::make_unique<Arguments>(std::move(args));
    return arguments;
}

std::unique_ptr<Expression> Parser::primary() {
    if (match({TokenType::Number})) {
        return std::make_unique<Literal>(previous().get_value(), TokenType::Number);
    }
    if (match({TokenType::Boolean})) {
        return std::make_unique<Literal>(previous().get_value(), TokenType::Boolean);
    }
    if (match({TokenType::String})) {
        return std::make_unique<Literal>(previous().get_value(), TokenType::String);
    }
    if (match({TokenType::Identifier})) {
        return std::make_unique<Identifier>(previous().get_value());
    }
    if (match({TokenType::ParenthesisOpen})) {
        auto expr = expression();
        if (!match({TokenType::ParenthesisClose})) {
            throw std::runtime_error("Expected closing parenthesis.");
        }
        return expr;
    }
    std::string unmatched_tokens;
    for (auto& token : tokens) {
        unmatched_tokens += token.get_value() + " ";
    }
    throw std::runtime_error("ERROR: Could not parse program, unmatched token: " + unmatched_tokens);
}
