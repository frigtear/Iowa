#include "scanner.h"
#include "parser.h"
#include "token.h"

int main(int argc, char* argv[]){
    if (argc != 2){
        fail("ERROR: pass in 1 argument");
    }

    char* path = argv[1];
    std::vector<Token> tokens = scan_source(path);
    

    Parser parser = Parser(tokens);
    

    Expression* expr = parser.parse();
    Parser::print_ast(expr);
}