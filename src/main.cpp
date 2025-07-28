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
    std::vector<Statement*> statements = parser.parse();

    for(auto& stmnt : statements){
        std::cout << "Evaluating statement";
        parser.evaluate_statement(stmnt);
    };

    return 0;
}