#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>
#include <variant>
#include "errors.h"
#include "token.h"

// Base for AST expressions
class Expression {
public:
    virtual ~Expression() = default;
};

// Declaration is the top‐level AST node (program holds Declarations)
class Declaration {
public:
    virtual ~Declaration() = default;
};

// Statements are also Declarations, so they can appear in the top‐level
class Statement : public Declaration {
public:
    virtual ~Statement() = default;
};

// Static (typed) variable declaration: e.g. "int x = 5;"
class StaticDeclaration : public Declaration {
public:
    TokenType type;
    std::string variable_name;
    std::variant<int, bool, std::string> variable_value;

    StaticDeclaration(TokenType t,
                      std::string name,
                      std::variant<int, bool, std::string> val)
        : type(t), variable_name(std::move(name)), variable_value(std::move(val)) {}
    
    ~StaticDeclaration() noexcept = default;
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

class Program {
public:
    std::vector<Declaration*> declarations;

    Program(std::vector<Declaration*> decls) : declarations(std::move(decls)) {}
    ~Program() {
        for (auto d : declarations)
            delete d;
    }
};

#endif 
