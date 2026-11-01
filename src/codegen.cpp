#include "codegen.h"
#include <stdexcept>

Codegen::Codegen() {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("Iowa", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
}

llvm::Value* Codegen::codegen_binary_expression(std::unique_ptr<BinaryExpression> binary_expression) {
    llvm::Value* lvalue = codegen_expression(std::move(binary_expression->left));
    llvm::Value* rvalue = codegen_expression(std::move(binary_expression->right));
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

llvm::Value* Codegen::codegen_expression(const Expression* expr) {
    return nullptr; // Placeholder until expression generation is implemented.
}
