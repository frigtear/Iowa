#include <string>
#include <iostream>
#include "errors.h"

Error::Error(std::string msg, std::string c, int ln) {
    message = msg;
    line_number = ln;
    culprit = c;
}

void Error::print() const{
    std::cout << "Error on line " << line_number << ": ";
    if (!culprit.empty()) {
        std::cout << culprit << ": ";
    }
    std::cout << message << std::endl;
}

void ErrorTracker::add_error(const std::string& message, const std::string& culprit, int line_number) {
    Error error(message, culprit, line_number);
    errors.push_back(error);
}

void ErrorTracker::print_all() {
    for (const auto& err : errors) {
        err.print();
    }
}

bool ErrorTracker::has_errors() const {
    return !errors.empty();
}
