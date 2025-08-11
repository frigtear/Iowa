#include "scanner.h"
#include "parser.h"
#include "token.h"
#include "evaluator.h"
#include <iostream>
#include <variant>

bool debug_mode = true;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: pass in 1 argument\n";
        return 1;
    }

    char* path = argv[1];
    std::vector<Token> tokens = scan_source(path);

    if (debug_mode){
        for (const Token& t : tokens) {
            std::cout << Token::get_type_string(t.get_type()) << ": " << t.get_value() << "\n";
        }
    }
    
    Parser parser(tokens);
    Evaluator evaluator;

    std::unique_ptr<Declaration> root = parser.program();
    evaluator.execute_program(dynamic_cast<Program*>(root.get()));

    return 0;
}