#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <variant>
#include <unordered_map>

#include "errors.h"
#include "lexemes.h"
#include "scanner.h"


void fail(std::string message){
    std::cerr << message;
    exit(1);
}

void add_token(std::vector<Lexeme>& tokens, std::string value, TokenType type){
    Lexeme lex(value, type);
    tokens.push_back(lex);
}

bool isNumeric(char character){
    return ('0' <= character  && character <= '9');
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

std::string scan_identifier(std::ifstream& source){

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

std::vector<Lexeme> scan_source(char* path){

    bool errored = false;
    int line_number = 0;
    char character;
    std::string value;

    std::vector<Error> errors;

    std::ifstream source_code(path);

    if (!source_code.is_open()){
        fail("ERROR: input file could not be opened");
    }

    std::vector<Lexeme> lexemes;

    while (source_code.get(character)){

        switch (character){

            case '(':
            {
                add_token(lexemes, "(", TokenType::Bracket_Open);
                break;
            }
            case ')':
            {
                add_token(lexemes, ")", TokenType::Bracket_Close);
                break;
            }
            case '{':
            {
                add_token(lexemes, "{", TokenType::Bracket_Open);
                break;
            }
            case '}':
                add_token(lexemes, "}", TokenType::Bracket_Close);
                break;
            case '+':{
                add_token(lexemes, "+", TokenType::Operator);
                break;
            }
            case '-':{
                add_token(lexemes, "-", TokenType::Operator);
                break;
            }
            case '=':{
                if (source_code.peek() == '='){
                    add_token(lexemes, "==", TokenType::Operator);
                    source_code.get();
                }
                else{
                    add_token(lexemes, "=", TokenType::Assignment);
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
                add_token(lexemes, value, TokenType::String_Literal);
                break;
            

            default:
                if (isNumeric(character)){
                    go_back_one(source_code);
                    std::string value = scan_digit(source_code);
                    add_token(lexemes, value, TokenType::Digit);
                    std::cout << "read digit: " << value << " from input" << std::endl;
                    break;
                }

                if (isalpha(character)){
                    go_back_one(source_code);
                    std::string value = scan_identifier(source_code);
                    add_token(lexemes, value, TokenType::Identifier);
                    std::cout << "read identifier: " << value << " from input" << std::endl;
                    break;
                }

                errored = true;
                Error error("Invalid Syntax", "", line_number);
                errors.push_back(error);

                
        }
    }
    return lexemes;

    /*
    if (errored){
        for(int i = 0; i<errors.size(); i++){
            errors.at(i).print();
        }
        return -1;
    }
        */
    
   // return 0;
}