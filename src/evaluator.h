#include "ast.h"
#include "environment.h"

#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator {
public:
    using evaluation = std::variant<int, double, std::string, bool>;

    Evaluator();
    ~Evaluator();

    void evaluate(const std::vector<Statement*>& statements);

    evaluation evaluate_expression(Expression* expr);
    evaluation evaluate_literal(Literal* literal);
    evaluation evaluate_identifier(Identifier* identifier);
    evaluation evaluate_binary(BinaryExpression* binary);

    void evaluate_statement(Declaration* statement);
    void evaluate_declaration(Declaration* declaration);
    void visit_expression_statement(ExpressionStatement* statement);
    void visit_print_statement(PrintStatement* stmt);
    void visit_dynamic_declaration(DynamicDeclaration* declaration);
    void visit_block_statement(Block* block);
    void visit_if_statement(IfStatement* if_stmnt);

    void execute_program(Program* program);

private:
    Environment* current_environment;
};

#endif