#include "ast.h"

#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator {
public:
    using Evaluation = std::variant<int, bool, std::string>;
    void evaluate(const std::vector<Statement*>& statements);

private:
    Evaluation evaluate_expression(Expression* expr);
    Evaluation evaluate_literal(Literal* literal);
    Evaluation evaluate_identifier(Identifier* identifier);
    Evaluation evaluate_binary(BinaryExpression* binary);

    void evaluate_statement(Statement* statement);
    void visit_expression_statement(ExpressionStatement* statement);
    void visit_print_statement(PrintStatement* stmt);
    void visit_declaration_statement(StaticDeclaration* declaration);
};

#endif