#include <iostream>
#include <string>
#include <cstdint>

#include "recursive_scan.cpp"
using namespace std;

struct {
    string* path;
    string* output_path;
} cli_arguments;

const auto get_cli_arguments(int n_args, const char** v_args) {
    string* raw_arguments[n_args - 1];

    for (uint8_t i = 0; i < n_args - 1; i++) {
        raw_arguments[i] = new string(v_args[i + 1]);
    }

    cli_arguments.path = raw_arguments[0]; // fisrt argument must be a path to directory to scan

    return &cli_arguments;
}

int main(int n_args, const char** v_args) {
    const auto args = get_cli_arguments(n_args, v_args);
    recursive_scan_ns::scan(*args->path);
    return 0;
}