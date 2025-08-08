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

Token scan_string(std::ifstream& source);

Token scan_digit(std::ifstream& source);

Token scan_identifier(std::ifstream& source);

void go_back_one(std::ifstream& source);

std::vector<Token> scan_source(char* path);

class Scanner{
    public:
        Scanner();
        
        void add_token(std::string token_value, TokenType token_type);
        void add_token(const Token& token);
        std::vector<Token> get_tokens();

    private:
        std::vector<Token> tokens; 
};

#endif
