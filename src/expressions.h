#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>
#include "errors.h"  


class Expression {
public:
    virtual ~Expression() = default;
};


class Literal : public Expression {
public:
    std::string value;

    Literal(const std::string& value) : value(value) {}
};


class Identifier : public Expression {
public:
    std::string name;

    Identifier(const std::string& name) : name(name) {}
};


class EqualityOperator : public Expression {
public:
    std::string op;

    EqualityOperator(const std::string& op) : op(op) {}
};


class ComparisonOperator : public Expression {
public:
    std::string op;

    ComparisonOperator(const std::string& op) : op(op) {}
};


class BinaryExpression : public Expression {
public:
    Expression* left;
    std::string op;
    Expression* right;

    BinaryExpression(Expression* left, const std::string& op, Expression* right)
        : left(left), op(op), right(right) {}

    ~BinaryExpression() {
        delete left;
        delete right;
    }
};


class Assignment : public Expression {
public:
    Identifier* variable;
    Expression* value;

    Assignment(Identifier* variable, Expression* value)
        : variable(variable), value(value) {}

    ~Assignment() {
        delete variable;
        delete value;
    }
};


class ExpressionStatement : public Expression {
public:
    Expression* expr;

    ExpressionStatement(Expression* expr) : expr(expr) {}

    ~ExpressionStatement() {
        delete expr;
    }
};


class Block : public Expression {
public:
    std::vector<Expression*> statements;

    Block(const std::vector<Expression*>& statements)
        : statements(statements) {}

    ~Block() {
        for (auto stmt : statements)
            delete stmt;
    }
};


class IfStatement : public Expression {
public:
    Expression* condition;
    Block* thenBlock;
    Block* elseBlock;  

    IfStatement(Expression* condition, Block* thenBlock, Block* elseBlock = nullptr)
        : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {}

    ~IfStatement() {
        delete condition;
        delete thenBlock;
        if (elseBlock) delete elseBlock;
    }
};

#endif 
