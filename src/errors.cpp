#include <string>
class Error{
    private:
        std::string name;
        std::string message;
        int line_number;

    public:
        Error(std::string n, std::string m, int ln){
            name = n;
            message = m;
            line_number = ln;
        }
};

Error create_error(std::string type, std::string msg, int ln){
    return Error(type, msg, ln);
}




