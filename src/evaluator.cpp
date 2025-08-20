#include "evaluator.h"
#include <variant>

Evaluator::Evaluator(){
    current_environment = std::make_unique<Environment>();
}

Evaluator::~Evaluator() = default;  

Evaluator::evaluation Evaluator::evaluate_literal(const Literal* literal) {
    if (!literal) {
        throw std::runtime_error("Null literal encountered");
    }

    std::string literal_value = literal->value;
    TokenType literal_type = literal->type;

    if (literal_type == TokenType::Number) {
        if (literal_value.empty()) {
            throw std::runtime_error("Literal value is empty");
        }
        return std::stoi(literal_value);
    } else if (literal_type == TokenType::Boolean) {
        if (literal_value == "true") {
            return true;
        } else if (literal_value == "false") {
            return false;
        } else {
            throw std::runtime_error("Unsupported boolean type");
        }
    }

    return literal_value;
}

Evaluator::evaluation Evaluator::evaluate_identifier(const Identifier* identifier) {
    return current_environment->get_variable_value(identifier->identifier_name); 
}


struct BinaryEvaluator {
    TokenType op;

    Evaluator::evaluation operator()(int l, int r) const {
        switch (op) {
            case TokenType::Plus:             return l + r;
            case TokenType::Minus:            return l - r;
            case TokenType::Multiply:         return l * r;
            case TokenType::Divide:
                if (r == 0) throw std::runtime_error("Division by zero");
                return l / r;

            case TokenType::GreaterThan:      return l > r;
            case TokenType::GreaterEqualsThan:return l >= r;
            case TokenType::LessThan:         return l < r;
            case TokenType::LessEqualsThan:   return l <= r;

            case TokenType::EqualsEquals:     return l == r;
            case TokenType::NotEqual:         return l != r;

            default:
                throw std::runtime_error("Unsupported integer op: " +
                                         Token::get_type_string(op));
        }
    }

    Evaluator::evaluation operator()(bool l, bool r) const {
        switch (op) {
            case TokenType::And:              return l && r;
            case TokenType::Or:               return l || r;
            case TokenType::EqualsEquals:     return l == r;
            case TokenType::NotEqual:         return l != r;
            default:
                throw std::runtime_error("Unsupported boolean op: " +
                                         Token::get_type_string(op));
        }
    }

    Evaluator::evaluation operator()(const std::string& l,
                                     const std::string& r) const {
        switch (op) {
            case TokenType::EqualsEquals:     return l == r;
            case TokenType::NotEqual:         return l != r;
            default:
                throw std::runtime_error("Unsupported string op: " +
                                         Token::get_type_string(op));
        }
    }

    template<typename L, typename R>
    Evaluator::evaluation operator()(L, R) const {
        throw std::runtime_error(
            "Type mismatch in binary expression: " +
            Token::get_type_string(op));
    }
};


Evaluator::evaluation Evaluator::evaluate_binary(const BinaryExpression* binary) {
    auto left  = evaluate_expression(binary->left.get());
    auto right = evaluate_expression(binary->right.get());
    TokenType op = binary->op;

    return std::visit(BinaryEvaluator{op}, left, right);
}

Evaluator::evaluation evaluate_call(const Call* call){
    throw std::runtime_error("function calls not implemented yet");
}

Evaluator::evaluation Evaluator::evaluate_expression(const Expression* expr) {
    if (!expr) {
        throw std::runtime_error("Null expression encountered during evaluation");
    }

    if (auto binary = dynamic_cast<const BinaryExpression*>(expr)) {
        return evaluate_binary(binary);
    } else if (auto identifier = dynamic_cast<const Identifier*>(expr)) {
        return evaluate_identifier(identifier);
    } else if (auto literal = dynamic_cast<const Literal*>(expr)) {
        return evaluate_literal(literal);
    } else if (auto call = dynamic_cast<const Call*>(expr)){
        return evaluate_call(call);
    }

    throw std::runtime_error("Unknown expression type");
}

void Evaluator::evaluate(const std::vector<Statement*>& statements) {
    for (Statement* stmt : statements) {
        evaluate_statement(stmt);
    }
}

void Evaluator::evaluate_declaration(const Declaration* declaration){
    if (!declaration){
        throw std::runtime_error("null declaration encountered during evaluation");
    }
    
    if (auto decl = dynamic_cast<const DynamicDeclaration*>(declaration)) {
        visit_dynamic_declaration(decl);
    }
    else if (auto stmnt = dynamic_cast<const Statement*>(declaration)){
        evaluate_statement(stmnt);
    }
    else{
        throw std::runtime_error("unknown declaration type");
    }
}

void Evaluator::evaluate_statement(const Declaration* declaration) {
    if (!declaration) {
        throw std::runtime_error("Null statement encountered during evaluation");
    }

    if (auto print_stmt = dynamic_cast<const PrintStatement*>(declaration)) {
        visit_print_statement(print_stmt);
    } else if (auto expr_stmt = dynamic_cast<const ExpressionStatement*>(declaration)) {
        visit_expression_statement(expr_stmt);
    } else if (auto block = dynamic_cast<const Block*>(declaration)){
        visit_block_statement(block, true);
    } else if (auto if_stmnt = dynamic_cast<const IfStatement*>(declaration)) {
        visit_if_statement(if_stmnt);
    } else if (auto loop_stmnt = dynamic_cast<const LoopStatement*>(declaration)){
        visit_loop_statement(loop_stmnt);
    } else {
        throw std::runtime_error("Unknown statement type");
    }
}

void Evaluator::visit_expression_statement(const ExpressionStatement* statement) {
    evaluate_expression(statement->expr.get());
}

void Evaluator::visit_print_statement(const PrintStatement* stmt) {
    evaluation value = evaluate_expression(stmt->expression.get());

    std::visit([](auto&& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, bool>) {
            std::cout << std::boolalpha << v;
        } else {
            std::cout << v;
        }
    }, value);

    std::cout << "\n";
}


void Evaluator::visit_dynamic_declaration(const DynamicDeclaration* declaration) {
    evaluation value = evaluate_expression(declaration->value.get());
    current_environment->add_variable(declaration->variable_name, value);
}

void Evaluator::visit_block_statement(const Block* block, bool use_new_scope) {

    if (use_new_scope){
        auto parent = std::move(current_environment);
        current_environment = std::make_unique<Environment>(parent.get());

        for (const auto& declaration : block->declarations) {
            evaluate_declaration(declaration.get());
        }
        current_environment = std::move(parent);
    }
    else{
        for (const auto& declaration : block->declarations) {
            evaluate_declaration(declaration.get());
        }
    }
 
}

void Evaluator::visit_if_statement(const IfStatement* if_stmnt){
    evaluation condition = evaluate_expression(if_stmnt->condition.get());
    bool condition_value;
    if (std::holds_alternative<bool>(condition)) {
        condition_value = std::get<bool>(condition);
    }

    if (condition_value == true){
        visit_block_statement(if_stmnt->if_block.get(), true);
    }
    else if (if_stmnt->has_else_block == true){
        visit_block_statement(if_stmnt->else_block.get(), true);
    }
}


void Evaluator::visit_loop_statement(const LoopStatement* loop){
    bool condition_value = true;
    while (condition_value == true){
        evaluation condition = evaluate_expression(loop->condition.get());

        if (!std::holds_alternative<bool>(condition)) {
            throw std::runtime_error("Loop condition must be boolean");
        }

        condition_value = std::get<bool>(condition);
        visit_block_statement(loop->loop_block.get(), false);
    }
}


void Evaluator::execute_program(const Program* program){
    auto& program_declarations = program->declarations;
    for (auto& declaration : program_declarations){
        evaluate_declaration(declaration.get());
    }
}