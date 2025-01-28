#ifndef ERRORS_H
#define ERRORS_H

#include <string>

class Error {
private:
    std::string message;
    std::string culprit;
    int line_number;

public:
    Error(std::string m, std::string c, int ln);
    void print();
};

#endif 
