#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "errors.h"

void fail(std::string message){
    std::cerr << message;
    exit(1);
}

int main(int argc, char* argv[]){

    bool errored = false;
    std::vector<Error> errors;
    if (argc != 2){
        fail("ERROR: pass in 1 argument");
    }

    char* path = argv[1];
    std::ifstream source_code(path);

    if (!source_code.is_open()){
        fail("ERROR: input file could not be opened");
    }
    
    char character;
    while (source_code.get(character)){
        std::cout << character << std::endl;
    }

    
    return 0;
}