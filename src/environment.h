#include <unordered_map>
#include <string>
#include <variant>

class Environment{
    public:
        using dynamic_type = std::variant<int, double, std::string, bool>;

        Environment();
        Environment(Environment* parent);

        dynamic_type get_variable_value(const std::string& variable_name) const;
        void add_variable(std::string name, dynamic_type value);
        void remove_variable(const std::string& name);
        bool has_reference(const std::string& name) const;
           
    private:
        std::unordered_map<std::string, dynamic_type> variables;
        Environment* parent;
};