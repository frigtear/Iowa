#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>
#include <variant>
#include <memory>

#include "errors.h"
#include "token.h"

class Expression {
public:
    virtual ~Expression() = default;
};

class Declaration {
public:
    virtual ~Declaration() = default;
};

class Statement : public Declaration{
public:
    virtual ~Statement() = default;
};

class DynamicDeclaration : public Declaration {
public:
    std::string variable_name;
    std::unique_ptr<Expression> value;

    DynamicDeclaration(std::string name,
                       std::unique_ptr<Expression> val)
        : variable_name(std::move(name)), value(std::move(val)) {}
};

class Literal : public Expression {
public:
    std::string value;
    TokenType type;

    Literal(std::string val, TokenType t)
        : value(std::move(val)), type(t) {}
};

class IdentifierExpr : public Expression {
public:
    std::string name;

    IdentifierExpr(std::string n)
        : name(std::move(n)) {}
};

class BinaryExpression : public Expression {
public:
    std::unique_ptr<Expression> left;
    TokenType op;
    std::unique_ptr<Expression> right;

    BinaryExpression(std::unique_ptr<Expression> l, TokenType o, std::unique_ptr<Expression> r) 
                     : left(std::move(l)), op(o), right(std::move(r)) {}
};

class Identifier : public Expression{
public:
    std::string identifier_name;

    Identifier(std::string name)
        : identifier_name(std::move(name)) {}
};


class Arguments : public Expression {
public:
    std::vector<std::unique_ptr<Expression>> arguments;

    Arguments(std::vector<std::unique_ptr<Expression>> args) : arguments(std::move(args)) {};
};


class Call : public Expression {
public:
    std::unique_ptr<Expression> callee;
    std::unique_ptr<Arguments> arguments;

    Call (std::unique_ptr<Expression> cl, std::unique_ptr<Arguments> args) : callee(std::move(cl)),  arguments(std::move(args)) {}
};


class Assignment : public Statement {
public:
    std::unique_ptr<IdentifierExpr> variable;
    std::unique_ptr<Expression> value;

    Assignment(std::unique_ptr<IdentifierExpr> var,
               std::unique_ptr<Expression> val)
        : variable(std::move(var)), value(std::move(val)) {}
};

class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> expr;

    ExpressionStatement(std::unique_ptr<Expression> e)
        : expr(std::move(e)) {}
};

class Block : public Statement {
public:
    std::vector<std::unique_ptr<Declaration>> declarations;

    Block(std::vector<std::unique_ptr<Declaration>> stmts)
        : declarations(std::move(stmts)) {}
};

class IfStatement : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> if_block;
    std::unique_ptr<Block> else_block;
    bool has_else_block;

    IfStatement(std::unique_ptr<Expression> cond,
                std::unique_ptr<Block> ib,
                std::unique_ptr<Block> eb)
        : condition(std::move(cond)),
          if_block(std::move(ib)),
          else_block(std::move(eb)) {
        if (else_block == nullptr){
            has_else_block = false;
        } else {
            has_else_block = true;
        }
    }
};

class LoopStatement : public Statement{
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> loop_block;

    LoopStatement(std::unique_ptr<Expression> cond,
                  std::unique_ptr<Block> lb)
        : condition(std::move(cond)), loop_block(std::move(lb)) {}
};

class PrintStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;

    PrintStatement(std::unique_ptr<Expression> expr)
        : expression(std::move(expr)) {}
};

class Program : public Declaration{
public:
    std::vector<std::unique_ptr<Declaration>> declarations;

    Program(std::vector<std::unique_ptr<Declaration>> decls)
        : declarations(std::move(decls)) {}
};

#endif // EXPRESSIONS_H
