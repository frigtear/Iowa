#pragma once
#include <variant>
#include <memory>
#include "ast.h"
#include "environment.h"

class Evaluator {
public:
    using evaluation = std::variant<int, double, std::string, bool>;

    Evaluator();
    ~Evaluator();
    
    void execute_program(const Program* program);
    void evaluate(const std::vector<std::unique_ptr<Statement>>& statements); 
    void evaluate(const std::vector<Statement*>& statements);               

    void evaluate_declaration(const Declaration* declaration);
    void evaluate_statement(const Declaration* declaration);

    void visit_expression_statement(const ExpressionStatement* statement);
    void visit_print_statement(const PrintStatement* stmt);
    void visit_dynamic_declaration(const DynamicDeclaration* declaration);
    void visit_block_statement(const Block* block, bool use_new_scope);
    void visit_if_statement(const IfStatement* if_stmnt);
    void visit_loop_statement(const LoopStatement* loop_stmnt);

    evaluation evaluate_expression(const Expression* expr);
    evaluation evaluate_binary(const BinaryExpression* binary);
    evaluation evaluate_identifier(const Identifier* identifier);
    evaluation evaluate_literal(const Literal* literal);

private:
    std::unique_ptr<Environment> current_environment; 
};
