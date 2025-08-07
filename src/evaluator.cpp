#include "evaluator.h"

Evaluator::Evaluator(){
    Environment* environment = new Environment;
    current_environment = environment;
}

Evaluator::~Evaluator() {
    delete current_environment;
}

Evaluator::evaluation Evaluator::evaluate_literal(Literal* literal) {
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

Evaluator::evaluation Evaluator::evaluate_identifier(Identifier* identifier) {
    return current_environment->get_variable_value(identifier->identifier_name); 
}

Evaluator::evaluation Evaluator::evaluate_binary(BinaryExpression* binary) {
    evaluation left = evaluate_expression(binary->left);
    evaluation right = evaluate_expression(binary->right);
    TokenType op = binary->op;

    return std::visit([&op](auto&& l, auto&& r) -> Evaluator::evaluation {
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
        } else if constexpr (std::is_same_v<L, bool> && std::is_same_v<R, bool>) {
            switch (op) {
                case TokenType::And: return l && r;
                case TokenType::Or:  return l || r;
                default:
                    throw std::runtime_error("Unsupported boolean operation");
            }
        } else {
            throw std::runtime_error("Unsupported operand types for binary expression");
        }
    }, left, right);
}

Evaluator::evaluation Evaluator::evaluate_expression(Expression* expr) {
    if (!expr) {
        throw std::runtime_error("Null expression encountered during evaluation");
    }

    if (auto binary = dynamic_cast<BinaryExpression*>(expr)) {
        return evaluate_binary(binary);
    } else if (auto identifier = dynamic_cast<Identifier*>(expr)) {
        return evaluate_identifier(identifier);
    } else if (auto literal = dynamic_cast<Literal*>(expr)) {
        return evaluate_literal(literal);
    }

    throw std::runtime_error("Unknown expression type");
}

void Evaluator::evaluate(const std::vector<Statement*>& statements) {
    for (Statement* stmt : statements) {
        evaluate_statement(stmt);
    }
}

void Evaluator::evaluate_declaration(Declaration* declaration){
    if (!declaration){
        throw std::runtime_error("null declaration encountered during evaluation");
    }
    
    if (auto decl = dynamic_cast<DynamicDeclaration*>(declaration)) {
        visit_dynamic_declaration(decl);
    }
    else if (auto stmnt = dynamic_cast<Statement*>(declaration)){
        evaluate_statement(stmnt);
    }
    else{
        throw std::runtime_error("unknown declaration type");
    }
}

void Evaluator::evaluate_statement(Declaration* declaration) {
    if (!declaration) {
        throw std::runtime_error("Null statement encountered during evaluation");
    }

    if (auto print_stmt = dynamic_cast<PrintStatement*>(declaration)) {
        visit_print_statement(print_stmt);
    } else if (auto expr_stmt = dynamic_cast<ExpressionStatement*>(declaration)) {
        visit_expression_statement(expr_stmt);
    } else if (auto block = dynamic_cast<Block*>(declaration)){
        visit_block_statement(block);
    } else {
        throw std::runtime_error("Unknown statement type");
    }
}

void Evaluator::visit_expression_statement(ExpressionStatement* statement) {
    evaluate_expression(statement->expr);
}

void Evaluator::visit_print_statement(PrintStatement* stmt) {
    evaluation value = evaluate_expression(stmt->expression);

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


void Evaluator::visit_dynamic_declaration(DynamicDeclaration* declaration) {
    evaluation value = evaluate_expression(declaration->value);
    //std::cout << "Adding value to variable " + declaration->variable_name << std::endl;
    current_environment->add_variable(declaration->variable_name, value);
}


void Evaluator::visit_block_statement(Block* block){
    Environment* prev = current_environment;
    current_environment = new Environment(prev);
    for (auto& declaration : block->declarations){
        evaluate_declaration(declaration);
    }
    current_environment = prev;
}


void Evaluator::execute_program(Program* program){
    std::vector<Declaration*> program_declarations = program->declarations;
    for (auto& declaration : program_declarations){
        evaluate_declaration(declaration);
    }
}