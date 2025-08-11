#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "token.h"
#include <vector>
#include <variant>
#include <memory>

class Parser {
public:
    using evaluation = std::variant<int, double, std::string, bool>;

    Parser(std::vector<Token> t);

    Token peek() const;
    Token previous();
    Token next();
    Token consume(TokenType expected, const std::string& errorMessage);

    bool is_at_end();
    bool match(std::vector<std::string> types);
    bool match(std::vector<TokenType> types);
    bool check(TokenType type) const;

    std::unique_ptr<Declaration> program();
    std::unique_ptr<Declaration> declaration();
    std::unique_ptr<Declaration> statement();
    std::unique_ptr<Declaration> dynamic_declaration();

    std::unique_ptr<Statement> print_statement();
    std::unique_ptr<Statement> if_statement();
    std::unique_ptr<Statement> expression_statement();
    std::unique_ptr<Statement> block();

    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> logic_or();
    std::unique_ptr<Expression> logic_and();
    std::unique_ptr<Expression> logic_lessThan();
    std::unique_ptr<Expression> logic_greaterThan();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> term();
    std::unique_ptr<Expression> factor();
    std::unique_ptr<Expression> primary();
    std::unique_ptr<Expression> assignment();
    std::unique_ptr<Expression> literal();
    std::unique_ptr<Expression> identifier();
    std::unique_ptr<Expression> number();
    std::unique_ptr<Expression> string_literal();
    std::unique_ptr<Expression> equality_operator();
    std::unique_ptr<Expression> comparison_operator();

private:
    std::vector<Token> tokens;
    int current;
    int number_of_tokens;
};

#endif 
