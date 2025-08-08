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


void Scanner::add_token(const Token& token){
    tokens.push_back(token);
}


std::vector<Token> Scanner::get_tokens(){
    return tokens;
}


Token scan_string(std::ifstream& source){

    std::string result = "";
    char current = 0;
    char next = source.peek();
    while (next != std::char_traits<char>::eof() && next != '"') {  
        current = source.get();  
        result += current;
    }

    source.get();
    return Token(result, TokenType::String);
}


Token scan_digit(std::ifstream& source) {
    std::string digit = "";
    char curr;
    char next = source.peek();

    while(next != std::char_traits<char>::eof() && isNumeric(next)){
        curr = source.get();
        next = source.peek();
        digit += curr;
    }

    return Token(digit, TokenType::Number);
};


std::string scan_word(std::ifstream& source) {
    std::string word = "";
    char next = source.peek();
    char curr; 

    while(next != std::char_traits<char>::eof() && isalnum(next)){
        curr = source.get();
        next = source.peek();
        word += curr;
    }
    return word;
};


Token scan_two_character_token(std::ifstream& source, char first, char second, TokenType first_type, TokenType second_type){
    if (source.peek() == second){
        source.get();
        std::string token_val {first, second};
        return Token(token_val, second_type);
    }
    std::string token_val {first};
    return Token(token_val, first_type);
}


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
                    break;
                }
            case '&':
                if (source_code.peek() == '&'){
                    scanner.add_token("&&", TokenType::And);
                    source_code.get();
                    break;
                }
            case '<':
                scanner.add_token(scan_two_character_token(source_code, '<', '=', TokenType::LessThan, TokenType::LessEqualsThan));
                break;
            case '>':
                scanner.add_token(scan_two_character_token(source_code, '>', '=', TokenType::GreaterThan, TokenType::GreaterEqualsThan));
                break;
            case '=':{
                scanner.add_token(scan_two_character_token(source_code, '=', '=', TokenType::Equals, TokenType::EqualsEquals));
                break;
            }
            case '\n':
                line_number++;
                break;
            case ' ':
                break;
            case '"':
                scanner.add_token(scan_string(source_code));  
                break;       
            case ';':
                scanner.add_token(";", TokenType::Semicolon);
                break;
            default:
                if (isNumeric(character)){
                    go_back_one(source_code);
                    scanner.add_token(scan_digit(source_code));
                    break;
                }

                if (isalpha(character)){
                    go_back_one(source_code);
                    std::string word = scan_word(source_code);
            
                    if (word == "if"){
                        scanner.add_token(word, TokenType::If);
                    }
                    else if (word == "else"){
                        scanner.add_token(word, TokenType::Else);
                    }
                    else if (word == "say"){
                        scanner.add_token(word, TokenType::Say);
                    }
                    else if (word == "set"){
                        scanner.add_token(word, TokenType::Set);
                    }
                    else if (word == "true"){
                        scanner.add_token(word, TokenType::Boolean);
                    }
                    else if (word == "false"){
                        scanner.add_token(word, TokenType::Boolean);
                    }
                    else{
                        scanner.add_token(word, TokenType::Identifier);
                    };       
                    break; 
                }
              
                errored = true;
                Error error("Invalid Syntax", "", line_number);
                errors.push_back(error);
        }
    }
    scanner.add_token("EOF", TokenType::Eof);
    return scanner.get_tokens();
}