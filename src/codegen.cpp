#include "codegen.h"
#include <stdexcept>

Codegen::Codegen() {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("Iowa", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
}

llvm::Value* Codegen::codegen_binary_expression(const BinaryExpression* binary_expression) {
    llvm::Value* lvalue = codegen_expression(binary_expression->left.get());
    llvm::Value* rvalue = codegen_expression(binary_expression->right.get());
    TokenType op = binary_expression->op;

    if (!lvalue || !rvalue){
        return nullptr;
    }

    switch (op) {
    case TokenType::Plus:
        return builder->CreateFAdd(lvalue, rvalue, "tmpadd");
    case TokenType::Minus:
        return builder->CreateFSub(lvalue, rvalue, "tmpsub");
    case TokenType::Multiply:
        return builder->CreateFMul(lvalue, rvalue, "tmpmlt");
    case TokenType::Divide:
        return builder->CreateFDiv(lvalue, rvalue, "tmldiv");
    default:
        throw std::runtime_error("codegen for binary expressions without +, -, *, / are not implemented yet");
    }
}

llvm::Value* Codegen::codegen_expression(const Expression* expression) {
    if (!expression) {
        throw std::runtime_error("Null expression encountered during code generation");
    }

    if (auto binary = dynamic_cast<const BinaryExpression*>(expression)) {
        return codegen_binary_expression(binary);
    }
    if (auto identifier = dynamic_cast<const Identifier*>(expression)) {
        return codegen_identifier(identifier);
    }
    if (auto literal = dynamic_cast<const Literal*>(expression)) {
        return codegen_literal(literal);
    }
    if (auto call = dynamic_cast<const Call*>(expression)) {
        return codegen_call(call);
    }

    throw std::runtime_error("Unknown expression type during code generation");
}

llvm::Value* Codegen::codegen_literal(const Literal* literal) {
    // TODO: Implement literal code generation.
    return nullptr;
}

llvm::Value* Codegen::codegen_identifier(const Identifier* identifier) {
    // TODO: Implement identifier code generation.
    return nullptr;
}

llvm::Value* Codegen::codegen_call(const Call* call) {
    // TODO: Implement function call code generation.
    return nullptr;
}

llvm::Function* Codegen::codegen_function_declaration(const FunctionDeclaration* declaration) {
    // TODO: Implement function definition code generation.
    return nullptr;
}
