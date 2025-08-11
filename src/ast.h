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

    DynamicDeclaration(
                    std::string name,
                    std::unique_ptr<Expression>  val)
        : variable_name(std::move(name)), value(std::move(val)) {}
};


class Literal : public Expression {
public:
    std::string value;
    TokenType type;
    Literal(const std::string& val, TokenType t) : value(val), type(t) {}
};


class IdentifierExpr : public Expression {
public:
    std::string name;
    IdentifierExpr(const std::string& n) : name(n) {}
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
    Identifier(const std::string& name) : identifier_name(name) {};
};

class Assignment : public Statement {
public:
    std::unique_ptr<IdentifierExpr> variable;
    std::unique_ptr<Expression> value;

    Assignment(std::unique_ptr<IdentifierExpr> var, std::unique_ptr<Expression> val)
        : variable(std::move(var)), value(std::move(val)) {}
};


class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> expr;
    ExpressionStatement(std::unique_ptr<Expression>e) : expr(std::move(e)) {}
};


class Block : public Statement {
public:
    std::vector<std::unique_ptr<Declaration>> declarations;
    Block(std::vector<std::unique_ptr<Declaration>> stmts) : declarations(std::move(stmts)) {}
};


class IfStatement : public Statement {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> if_block;
    std::unique_ptr<Block> else_block;
    bool has_else_block;


    IfStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Block> ib, std::unique_ptr<Block>  eb) : condition(std::move(cond)), if_block(std::move(ib)), else_block(std::move(eb)) {
        if (else_block == nullptr){
            has_else_block = false;
        }
        else{
            has_else_block = true;
        }
    };
};


class PrintStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;
    PrintStatement(std::unique_ptr<Expression> expr) : expression(std::move(expr)) {}
};

class Program : public Declaration{
public:
    std::vector<std::unique_ptr<Declaration>> declarations;

    Program(std::vector<std::unique_ptr<Declaration>> decls) : declarations(std::move(decls)) {}
   
};

#endif 
