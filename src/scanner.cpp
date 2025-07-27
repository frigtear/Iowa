#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "errors.h"
#include "token.h"
#include "scanner.h"


void fail(std::string message){
    std::cerr << message;
    exit(1);
}

bool isNumeric(char character){
    return ('0' <= character  && character <= '9');
}

Scanner::Scanner(){
    tokens = std::vector<Token> {};
};

void Scanner::add_token(std::string token_value, TokenType token_type){
    Token token(token_value, token_type);
    tokens.push_back(token);
};

std::vector<Token> Scanner::get_tokens(){
    return tokens;
}

std::string scan_string(std::ifstream& source){

    std::string result = "";
    char current = 0;

    while (source.peek() != EOF && source.peek() != '"') {  
        current = source.get();  
        result += current;
    }

    source.get();
    return result;
}

std::string scan_digit(std::ifstream& source){

    std::string digit = "";
    char curr;
    char next = source.peek();

    while(next != EOF && isNumeric(next)){
        curr = source.get();
        next = source.peek();
        digit += curr;
    }

    return digit;
};

std::string scan_word(std::ifstream& source){

    std::string identifier = "";
    char next = source.peek();
    char curr; 

    while(next != EOF && isalnum(next)){
        curr = source.get();
        next = source.peek();
        identifier += curr;
    }

    return identifier;
};

void go_back_one(std::ifstream& source) {
    std::streampos position = source.tellg(); 

    if (position != std::streampos(-1) && position > 0) {  
        source.seekg(position - std::streamoff(1));
    }
}

std::vector<Token> scan_source(char* path){

    bool errored = false;
    int line_number = 0;
    char character;
    std::string value;

    std::vector<Error> errors;

    std::ifstream source_code(path);

    if (!source_code.is_open()){
        fail("ERROR: input file could not be opened");
    }

    Scanner scanner;

    while (source_code.get(character)){

        switch (character){

            case '(':
            {
                scanner.add_token("(", TokenType::ParenthesisOpen);
                break;
            }
            case ')':
            {
                scanner.add_token(")", TokenType::ParenthesisClose);
                break;
            }
            case '{':
            {
                scanner.add_token("{", TokenType::BracketOpen);
                break;
            }
            case '}':
                scanner.add_token("}", TokenType::BracketClose);
                break;
            case '+':{
                scanner.add_token("+", TokenType::Plus);
                break;
            }
            case '-':{
                scanner.add_token("-", TokenType::Minus);
                break;
            }
            case '*': {
                scanner.add_token("*", TokenType::Multiply);
                break;
            }
            case '/': {
                scanner.add_token("/", TokenType::Divide);
                break;
            }
            case '|':
                if (source_code.peek() == '|'){
                    scanner.add_token("||", TokenType::Or);
                    source_code.get();
                }
                break;
            case '&':
                if (source_code.peek() == '&'){
                    scanner.add_token("&&", TokenType::And);
                    source_code.get();
                }
                break;
            case '=':{
                if (source_code.peek() == '='){
                    scanner.add_token("==", TokenType::EqualsEquals);
                    source_code.get();
                }
                else{
                    scanner.add_token("=", TokenType::Equals);
                }
                break;
            
            }
            case '\n':
                line_number++;
                break;

            case ' ':
                break;

            case '"':
                value = scan_string(source_code);
                std::cout << "read string: " << value << " from source code" << std::endl;
                scanner.add_token(value, TokenType::String);         

            default:
                if (isNumeric(character)){
                    go_back_one(source_code);
                    std::string value = scan_digit(source_code);
                    scanner.add_token(value, TokenType::Number);
                    break;
                }

                if (isalpha(character)){
                    go_back_one(source_code);
                    std::string value = scan_word(source_code);
            
                    if (value == "if"){
                        scanner.add_token(value, TokenType::If);
                    }
                    else if (value == "else"){
                        scanner.add_token(value, TokenType::Else);
                    }
                    else if (value == "say"){
                        scanner.add_token(value, TokenType::Say);
                    }
                    else if (value == "true"){
                        scanner.add_token(value, TokenType::Boolean);
                    }
                    else if (value == "false"){
                        scanner.add_token(value, TokenType::Boolean);
                    }
                    else{
                        scanner.add_token(value, TokenType::Identifier);
                    };       
                    break; 
                }
              
                errored = true;
                Error error("Invalid Syntax", "", line_number);
                errors.push_back(error);
        }
    }
    return scanner.get_tokens();
}