#include <iostream>
#include <string>
#include <cstdint>

#include "cli_arguments.cpp"

using namespace cli_arguments_ns;
using namespace std;

int main(int n_args, const char** v_args) {
    const auto args = get_cli_arguments(n_args, v_args);
    cout << "\n" << *args->path;
    return 0;
}