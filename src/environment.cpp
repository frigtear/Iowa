#include "environment.h"

Environment::Environment() : parent(nullptr) {};

Environment::Environment(Environment* env) : parent(env) {};

Environment::dynamic_type Environment::get_variable_value(const std::string& name) const {
    if (variables.contains(name)) {
        return variables.at(name); 
    } else if (parent != nullptr && parent->has_reference(name)){
        return parent->get_variable_value(name);
    }
    else{
        throw std::runtime_error(
        std::string{"Error: variable '"} + name + "' does not exist");
    }
}

void Environment::add_variable(std::string name, dynamic_type variable){
    variables.insert_or_assign(std::move(name), std::move(variable));
}

void Environment::remove_variable(const std::string& name){
    variables.erase(name);
}

bool Environment::has_reference(const std::string& name) const{
    return variables.contains(name);
}

