#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>
#include <regex>
#include <format>

#include "include/cli_arguments.hpp"

using namespace std;

#define THROW_COLOR_RANGE_EXP \
    throw ArgumentException("Color range (--color) must be specified in form of '#xxxxxx-#xxxxxx', where x is a hexadecimal digit (0-f)");

#define THROW_WRONG_TYPE_EXP \
    throw ArgumentException("type (-t) argument must be set to 'b' (box) or 't' (tree)");

#define THROW_WRONG_PATH_EXP(path) \
    throw ArgumentException(vformat("Path \"{0}\" is invalid. Input and output paths must be in a Unix style", make_format_args(path)));

//#define THROW_UNKNOWN_ARGUMENT_EXP(raw_argument) \
//    throw ArgumentException(vformat("Unknown argument {0}!! Please, check specified arguments again", make_format_args(raw_argument)));

namespace cli_arguments_ns {
    class ArgumentException : public exception {
    private:
        string _message;
    public:
        ArgumentException(const char* message) : _message(message) {}
        ArgumentException(string message) : _message(message) {}

        const char* what() const noexcept override {
            return this->_message.c_str();
        }
    };

    CliArguments cli_arguments;

    void throw_usage_message() {
        ifstream file("../USAGE.txt", ios::binary | std::ios::ate);
        if (!file.is_open()) {
            throw ArgumentException("Sorry, seem like the 'USAGE.txt' file is missing, please refer to the README.md file or github page for instructions");
            exit(1);
        }
        
        uint size = file.tellg();
        file.seekg(0);

        char* message = new char[size + 1];
        file.read(message, 1000);
        const ArgumentException exp(message);
        file.close();
        delete message;
        throw exp;
    }

    void set_argument_color(CliArguments& cli_arguments, const char** v_args, uint8_t& i) {
        string raw_argument = string(v_args[i]);
        char* start_color = new char[8], *end_color = new char[8];
        string value = v_args[++i];
        regex pattern("#([0-9]|[a-f]){6}-#([0-9]|[a-f]){6}");
        smatch match_info;

        if (!regex_match(value, match_info, pattern)) {
            THROW_COLOR_RANGE_EXP;
        }

        sscanf(value.c_str(), "%7s-%7s", start_color, end_color);

        cli_arguments.start_color = start_color;
        cli_arguments.end_color = end_color;
    }
    void set_argument_type(CliArguments& cli_arguments, const char** v_args, uint8_t& i) {
        string value(v_args[++i]);

        assert_type(value);

        cli_arguments.type = value[0];
    }

    void assert_type(string value){
        regex pattern("b|t|(box)|(tree)");
        smatch match_info;

        if (!regex_match(value, match_info, pattern))
            THROW_WRONG_TYPE_EXP;
    }

    void assert_path(string value) {
        regex pattern("^((/|.|..)[^/\\0]+)*(/)?$");
        smatch match_info;

        if (!regex_match(value, match_info, pattern)) {
            THROW_WRONG_PATH_EXP(value);
        }
    }

    CliArguments& get_cli_arguments(int n_args, const char** v_args) {
        // method, that records all cli arguments directly from the main function
        CliArguments& cli_arguments = cli_arguments_ns::cli_arguments;

        assert_path(v_args[1]);
        cli_arguments.path = string(v_args[1]);

        for (uint8_t i = 2; i < n_args; i++) {
            const string raw_argument = v_args[i];

            if (raw_argument.substr(0, 2) == "--") {
                const string arg_name = raw_argument.substr(2);

                if (arg_name == "color") {
                    set_argument_color(cli_arguments, v_args, i);
                }
                else if (arg_name == "type") {
                    set_argument_type(cli_arguments, v_args, i);
                }
                else if (arg_name == "help") {
                    throw_usage_message();
                }
            } else if (raw_argument[0] == '-') {
                // this is an argument declaration
                const char arg_name = raw_argument[1];
                char value = 0;

                switch (arg_name) {
                    // checking the symbol, that comes after the '-'
                    case 't': // type specified
                        set_argument_type(cli_arguments, v_args, i);
                        break;
                    case 'b':
                    case 'k':
                    case 'm':
                    case 'g': // doing like that because all these case requies same logic (set of size units)
                        cli_arguments.size_units = arg_name;
                        break;

                    case 'o': // output path was specified
                        cli_arguments.output_path = string(v_args[++i]);
                        assert_path(cli_arguments.output_path);
                        break;

                    default:
                        throw_usage_message();
                }
            }
        }
    
        return cli_arguments;
    }
}