#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <string>
#include <vector>
#include "errors.h"  // Assuming you have a file for handling errors

// Base class for all expressions
class Expression {
public:
    virtual ~Expression() = default;
};

// Literal values (Number or String)
class Literal : public Expression {
public:
    std::string value;

    Literal(const std::string& value) : value(value) {}
};

// Identifier
class Identifier : public Expression {
public:
    std::string name;

    Identifier(const std::string& name) : name(name) {}
};

// EqualityOperator (==, !=)
class EqualityOperator : public Expression {
public:
    std::string op;

    EqualityOperator(const std::string& op) : op(op) {}
};

// ComparisonOperator (<, >, <=, >=)
class ComparisonOperator : public Expression {
public:
    std::string op;

    ComparisonOperator(const std::string& op) : op(op) {}
};

// Binary Expression (for any binary operation: +, -, *, /, ==, !=, etc.)
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

// Assignment
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

// Expression statement
class ExpressionStatement : public Expression {
public:
    Expression* expr;

    ExpressionStatement(Expression* expr) : expr(expr) {}

    ~ExpressionStatement() {
        delete expr;
    }
};

// Block: a sequence of statements
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

// If statement
class IfStatement : public Expression {
public:
    Expression* condition;
    Block* thenBlock;
    Block* elseBlock;  // Can be nullptr

    IfStatement(Expression* condition, Block* thenBlock, Block* elseBlock = nullptr)
        : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {}

    ~IfStatement() {
        delete condition;
        delete thenBlock;
        if (elseBlock) delete elseBlock;
    }
};

#endif // EXPRESSIONS_H
