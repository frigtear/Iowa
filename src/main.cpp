#include "scanner.h"
#include "parser.h"
#include "token.h"
#include <iostream>
#include <variant>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: pass in 1 argument\n";
        return 1;
    }

    char* path = argv[1];
    std::vector<Token> tokens = scan_source(path);
    
    for (const Token& t : tokens) {
        std::cout << Token::get_type_string(t.get_type()) << ": " << t.get_value() << "\n";
    }

    Parser parser(tokens);
    Expression* expr = parser.parse();

    Parser::print_ast(expr);

    try {
        Parser::evaluation result = parser.evaluate_expression(expr);

        std::visit([](const auto& value) {
            std::cout << "Result: " << value << std::endl;
        }, result);
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}