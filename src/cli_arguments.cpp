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
    -o      string,     path to a file (.jpg, .png, .svg, .pdf) where resulting PlantUML schema will be drawn

    size will be shown only if corresponding argument (-b, -k, -m, -g) is passed
    if output file isn't provided - resulting schema will be shown without saving
*/

namespace cli_arguments_ns {
    struct {
        // dedicated structure, that will store values of every arguments
        string* path;
        char type; // b | t
        char size_units;
        string* output_path;
    } cli_arguments;

    const auto get_cli_arguments(int n_args, const char** v_args) {
        // method, that records all cli arguments directly from the main function
        string* raw_arguments[n_args - 1];

        for (uint8_t i = 0; i < n_args - 1; i++) {
            raw_arguments[i] = new string(v_args[i + 1]);
            //cout << *raw_arguments[i] << " ";
        }
    
        cli_arguments.path = raw_arguments[0];
    
        return &cli_arguments;
    }
}