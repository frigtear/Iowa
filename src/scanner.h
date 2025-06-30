#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"
#include "errors.h"


void fail(std::string message);

void add_token(std::vector<Token>& tokens, std::string value, TokenType type);

bool isNumeric(char character);

std::string scan_string(std::ifstream& source);

std::string scan_digit(std::ifstream& source);

std::string scan_identifier(std::ifstream& source);

void go_back_one(std::ifstream& source);

std::vector<Token> scan_source(char* path);

class Scanner{
    public:
        Scanner();
        
        void add_token(std::string token_value, TokenType token_type);
        std::vector<Token> get_tokens();

    private:
        std::vector<Token> tokens; 
};

#endif
