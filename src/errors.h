#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <vector>
#include <iostream>

class Error {
public:
    Error(std::string m, std::string c, int ln);
    Error(std::string msg) : message(msg), culprit(""), line_number(-1) {}

    void print() const;

private:
    std::string message;
    std::string culprit;
    int line_number;
};

class ErrorTracker {
private:
    std::vector<Error> errors;

public:
    void add_error(const std::string& message, const std::string& culprit, int line_number);
    void print_all();
    bool has_errors() const;
};

#endif
