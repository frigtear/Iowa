#include <unordered_map>
#include <string>

class Environment{
    public:
        std::unordered_map<std::string, std::variant<std::string, bool, int>> get_variable();
        void add_variable();
        void free_variable();
    private:
        std::unordered_map<std::string, std::variant<std::string, bool, int>> variables;
};