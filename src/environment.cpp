#include "environment.h"


const Environment::dynamic_type Environment::get_variable_value(const std::string& name) {
    if (variables.contains(name)) {
        return variables.at(name); 
    } else {
        throw std::runtime_error(
            std::string{"Error: variable '"} + name + "' does not exist");
    }
}

void Environment::add_variable(std::string name, dynamic_type variable){
    variables.emplace(std::move(name), std::move(variable));
}

void Environment::remove_variable(const std::string& name){
    variables.erase(name);
}