#include <unordered_map>
#include <string>
#include <variant>

class Environment{
    public:
        using dynamic_type = std::variant<std::string, bool, int>;

        Environment() = default;

        const dynamic_type get_variable_value(const std::string& variable_name);
        void add_variable(std::string name, dynamic_type value);
        void remove_variable(const std::string& name);
    private:
        std::unordered_map<std::string, dynamic_type> variables;

    
};