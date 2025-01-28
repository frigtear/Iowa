#include <string>
#include <iostream>
#include "errors.h"


Error::Error(std::string msg, std::string c, int ln){
    message = msg;
    line_number = ln;
    culprit = c;
}

void Error::print(){
    std::cout << "Error on line " << line_number << ": ";
    std::cout << culprit;
    std::cout << message << std::endl;
}


