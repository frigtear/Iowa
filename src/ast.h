#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>
#include <variant>
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

class DeclarationStatement : public Statement {
public:
    std::string variable_name;
    Expression* val;

    DeclarationStatement(
                    std::string name,
                    Expression* val)
        : variable_name(std::move(name)), val(std::move(val)) {}
    
    ~DeclarationStatement() noexcept = default;
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
    Expression* left;
    TokenType op;
    Expression* right;

    BinaryExpression(Expression* l, TokenType o, Expression* r)
        : left(l), op(o), right(r) {}
    ~BinaryExpression() {
        delete left;
        delete right;
    }
};

class Identifier : public Expression{

};

class Assignment : public Statement {
public:
    IdentifierExpr* variable;
    Expression* value;

    Assignment(IdentifierExpr* var, Expression* val)
        : variable(var), value(val) {}
    ~Assignment() {
        delete variable;
        delete value;
    }
};


class ExpressionStatement : public Statement {
public:
    Expression* expr;
    ExpressionStatement(Expression* e) : expr(e) {}
    ~ExpressionStatement() {
        delete expr;
    }
};


class Block : public Statement {
public:
    std::vector<Statement*> statements;
    Block(std::vector<Statement*> stmts) : statements(std::move(stmts)) {}
    ~Block() {
        for (auto s : statements)
            delete s;
    }
};


class IfStatement : public Statement {
public:
    Expression* condition;
    Block* thenBlock;
    Block* elseBlock;  

    IfStatement(Expression* cond, Block* t, Block* e = nullptr)
        : condition(cond), thenBlock(t), elseBlock(e) {}
    ~IfStatement() {
        delete condition;
        delete thenBlock;
        if (elseBlock) delete elseBlock;
    }
};


class PrintStatement : public Statement {
public:
    Expression* expression;
    PrintStatement(Expression* expr) : expression(expr) {}
    ~PrintStatement() {
        delete expression;
    }
};

class Program : public Declaration{
public:
    std::vector<Declaration*> declarations;

    Program(std::vector<Declaration*> decls) : declarations(decls) {}
    ~Program() {
        for (auto d : declarations)
            delete d;
    }
};

#endif 
