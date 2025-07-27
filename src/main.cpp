#include "include/cli_arguments.hpp"
#include "include/recursive_scan.hpp"
#include "include/plantuml_schema.hpp"

/*
    Basic workflow:
    Create code for plantuml, write it to the stdout
*/

int main(int n_args, const char** v_args) {
    try {
        cli_arguments_ns::CliArguments& args = cli_arguments_ns::get_cli_arguments(n_args, v_args);
        vector<recursive_scan_ns::FilesystemEntry>& seq = recursive_scan_ns::scan(args.path);
        plantuml_schema_ns::create_schema(seq, args);
    } catch(const exception& exp) {
        // gracefully exiting with error
        cerr << exp.what() << endl;
        return 1;
    }
    return 0;
}