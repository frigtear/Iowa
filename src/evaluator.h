#include "ast.h"
#include "environment.h"

#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator {
public:
    using evaluation = std::variant<int, double, std::string, bool>;

    void evaluate(const std::vector<Statement*>& statements);

    evaluation evaluate_expression(Expression* expr);
    evaluation evaluate_literal(Literal* literal);
    evaluation evaluate_identifier(Identifier* identifier);
    evaluation evaluate_binary(BinaryExpression* binary);

    void evaluate_statement(Statement* statement);
    void evaluate_declaration(Declaration* declaration);
    void visit_expression_statement(ExpressionStatement* statement);
    void visit_print_statement(PrintStatement* stmt);
    void visit_declaration_statement(DeclarationStatement* declaration);
    void visit_block_statement(Block* block, Environment* environment);

private:
    Environment* current_environment;
};

#endif