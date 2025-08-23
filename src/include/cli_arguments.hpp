#pragma once

#include <iostream>
#include <string>
#include <cstdint>
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
        if file was provided without extension or extension is other than these, ASCII scheme will be written

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

typedef unsigned int uint;

namespace cli_arguments_ns {
    typedef struct {
        // dedicated structure, that will store values of every arguments
        string path = "";
        char type = 't'; // box | tree
        char size_units = '\0'; // b | k | m | g
        string start_color = ""; // blue
        string end_color = ""; // red
        string output_path = "";
    } CliArguments;

    void throw_usage_message();

    void set_argument_color(CliArguments& cli_arguments, const char** v_args, uint8_t& i);
    void set_argument_type(CliArguments& cli_arguments, const char** v_args, uint8_t& i);

    void assert_type(string value);
    void assert_path(string value);

    CliArguments& get_cli_arguments(int , const char**);
}