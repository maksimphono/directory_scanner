#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>

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

namespace cli_arguments_ns {
    class ArgumentException : public exception {
    private:
        string _message;
    public:
        ArgumentException(const char* message) : _message(message) {}

        const char* what() const noexcept override {
            return this->_message.c_str();
        }
    };
    CliArguments cli_arguments;

    void set_argument_color(CliArguments& cli_arguments, const char** v_args, uint8_t& i) {
        string raw_argument = string(v_args[i]);
        char* start_color = new char[8], *end_color = new char[8];
        string value = v_args[++i];

        sscanf(value.c_str(), "%7s-%7s", start_color, end_color);
        cli_arguments.start_color = start_color;
        cli_arguments.end_color = end_color;
    }
    void set_argument_type(CliArguments& cli_arguments, const char** v_args, uint8_t& i) {
        char value = *v_args[++i];

        if (value != 'b' && value != 't')
            // TODO: implement more informative error message
            throw ArgumentException("type (-t) argument must be set to 'b' (box) or 't' (tree)");
        else
            cli_arguments.type = value;
    }

    CliArguments& get_cli_arguments(int n_args, const char** v_args) {
        // method, that records all cli arguments directly from the main function
        CliArguments& cli_arguments = cli_arguments_ns::cli_arguments;

        for (uint8_t i = 2; i < n_args; i++) {
            const string raw_argument = v_args[i];
            //string* raw_argument = new string(v_args[i + 1]);

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
                            cli_arguments.output_path = new string(v_args[++i]);
                            break;

                        default:
                            // TODO: implement more informative error message
                            throw ArgumentException("Unknown argument!!");
                    }
                }
            }
        cli_arguments.path = new string(v_args[1]);
    
        return cli_arguments;
    }
}