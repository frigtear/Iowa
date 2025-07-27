#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "token.h"
#include <vector>
#include <variant>
// Include the header where Object is defined

class Parser{
    public:

        using evaluation = std::variant<int, double, std::string, bool>;

        Parser(std::vector<Token> t);

        Token peek();
        Token previous();
        Token next();

        bool match(std::vector<std::string> types);
        bool match(std::vector<TokenType> types);    

        Expression* expression();
        Expression* logic_or();
        Expression* logic_and();
        Expression* equality();
        Expression* comparison();
        Expression* term();
        Expression* primary();
        Expression* factor();
        Expression* assignment();
        Expression* expression_statement();
        Expression* if_statement();
        Expression* literal();
        Expression* identifier();
        Expression* number();
        Expression* string_literal(); 
        Expression* equality_operator();
        Expression* comparison_operator();
        Expression* parse();

        static void print_ast(Expression* root);

        evaluation evaluate_literal(Literal* literal);
        evaluation evaluate_identifier(Identifier* identifier);
        evaluation evaluate_binary(BinaryExpression* binary);

        evaluation evaluate_expression(Expression* root);

        

    private: 
        std::vector<Token> tokens;
        int current;
        int number_of_tokens;
};

#endif  