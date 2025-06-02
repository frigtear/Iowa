#include "scanner.h"
#include "parser.h"
#include "lexemes.h"

int main(int argc, char* argv[]){
    if (argc != 2){
        fail("ERROR: pass in 1 argument");
    }

    char* path = argv[1];
    std::vector<Lexeme> lexemes = scan_source(path);
    
    for (const auto& lex : lexemes) {
        std::cout << lex.get_type_string() << "  ___  " << lex.get_value() << " ___ ";
    }
}