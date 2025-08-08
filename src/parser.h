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

        Token peek() const;
        Token previous();
        Token next();
        Token consume(TokenType expected, const std::string& errorMessage);
        
        bool is_at_end();
        bool match(std::vector<std::string> types);
        bool match(std::vector<TokenType> types);    
        bool check(TokenType type) const;

        Declaration* program();
        Statement* print_statement();
        void visit_print_statement(PrintStatement* statement );
        Statement* if_statement();
        Statement* expression_statement();
        
        Declaration* dynamic_declaration();
        Statement* block();

        Declaration* declaration();
        Declaration* statement();
        Expression* expression();
        Expression* logic_or();
        Expression* logic_and();
        Expression* logic_lessThan();
        Expression* logic_greaterThan();
        Expression* equality();
        Expression* comparison();
        Expression* term();
        Expression* primary();
        Expression* factor();
        Expression* assignment();
        Expression* literal();
        Expression* identifier();
        Expression* number();
        Expression* string_literal(); 
        Expression* equality_operator();
        Expression* comparison_operator();
        
    private: 
        std::vector<Token> tokens;
        int current;
        int number_of_tokens;
};

#endif  