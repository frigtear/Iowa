#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
private:
    std::string name;
    std::string message;
    int line_number;

public:
    // Constructor declaration
    Error(const std::string& n, const std::string& m, int ln);

    // Getter functions (optional, declarations)
    const std::string& getName() const;
    const std::string& getMessage() const;
    int getLineNumber() const;
};

Error create_error(const std::string& type, const std::string& msg, int ln);

#endif // ERROR_H
