#pragma once

#include "ast.h"
#include <memory>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

class Codegen {
public:
    Codegen();

    llvm::Value* codegen_binary_expression(const BinaryExpression* binary_expression);
    llvm::Value* codegen_expression(const Expression* expression);
    llvm::Value* codegen_literal(const Literal* literal);
    llvm::Value* codegen_identifier(const Identifier* identifier);
    llvm::Value* codegen_call(const Call* call);
    llvm::Function* codegen_function_declaration(const FunctionDeclaration* declaration);

private:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
};
