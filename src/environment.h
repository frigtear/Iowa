#include <unordered_map>
#include <string>
#include <variant>
#include <memory>
#include "ast.h"

class Environment;

class Callable{
    public:
        Callable(Statement* c) : code(std::move(c)) {};
        std::string get_name();
        Statement* get_code() const;
        Environment& get_closure() const;
    private:
        std::string name;
        Statement* code;
        std::shared_ptr<Environment> closure;
};

class Environment{
    public:
        using dynamic_type = std::variant<int, double, std::string, bool, std::shared_ptr<Callable>>;

        Environment();
        Environment(Environment* parent);
        Environment(std::unordered_map<std::string, dynamic_type> env);

        dynamic_type get_variable_value(const std::string& variable_name) const;
        void add_variable(std::string name, dynamic_type value);
        void remove_variable(const std::string& name);
        bool has_reference(const std::string& name) const;
           
    private:
        std::unordered_map<std::string, dynamic_type> variables;
        Environment* parent;
};