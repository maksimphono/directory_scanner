#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <regex>
#include <format>

#include "include/cli_arguments.hpp"

using namespace std;

/*
    Arguments description:

    -t      b | t (t by default)    type of the resulting schema. Can be tree (t) or box (b)
    -b      boolean, if set - size of each object (in bytes) will be printed alonside the name
    -k      boolean, if set - size of each object (in kilobytes) will be printed alonside the nameboolean, if set - size of each object (in kilobytes) will be printed alonside the name
    -m      boolean, if set - size of each object (in megabytes) will be printed alonside the name
    -g      boolean, if set - size of each object (in gigabytes) will be printed alonside the name    
    --color string of form "#xxx-#yyy"      color scale, which will be applyed to color the objects according to their sizes
        if value wan't specified, default "#00f-#f00" (blue-red) will be used
    -o      string,     path to a file (can be JPG, PNG, SVG, PDF or TXT for ascii-style scheme) where resulting PlantUML schema will be drawn, 
        if file was provide {
            return this->_message.c_str();
        }d without extension or extension is other than these, ASCII scheme will be written

    size will be shown only if corresponding argument (-b, -k, -m, -g) is passed
    if output file wasn't provided - resulting schema will be shown as PNG image without saving
    if same argument was provided with different values, only the last value will be used

    Example:

        $ main /path/to/dir -t b -k -m --color #ada-#f00 -o /path/to/output/schema.pdf

        Will create box schema of /path/to/dir directory, 
        specifying size of each object in megabytes, 
        will apply color scale from #ada (min value) to #f00 (max value)
        and save resulting schema as PDF into the file /path/to/output/schema.pdf
*/

#define THROW_COLOR_RANGE_EXP \
    throw ArgumentException("Color range (--color) must be specified in form of '#xxxxxx-#xxxxxx', where x is a hexadecimal digit (0-f)");

#define THROW_WRONG_TYPE_EXP \
    throw ArgumentException("type (-t) argument must be set to 'b' (box) or 't' (tree)");

#define THROW_WRONG_PATH_EXP \
    throw ArgumentException("Input and output paths must be in a Unix style");

#define THROW_UNKNOWN_ARGUMENT_EXP(raw_argument) \
    throw ArgumentException(vformat("Unknown argument {0}!! Please, check specified arguments again", make_format_args(raw_argument)));

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
            THROW_WRONG_PATH_EXP;
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
                        THROW_UNKNOWN_ARGUMENT_EXP(raw_argument);
                }
            }
        }
    
        return cli_arguments;
    }
}