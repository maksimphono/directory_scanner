#pragma once

#include <format>
#include <iostream>
#include <string>
#include "recursive_scan.hpp"
#include "cli_arguments.hpp"

using namespace std;
//using namespace recursive_scan_ns;

namespace plantuml_schema_ns {
    typedef enum {ASCII, JPG, PNG, SVG, PDF} OutputType;
    typedef enum {TREE, BOX} SchemaType;

    OutputType extract_output_file_type(string* output_path);

    struct {
        string path;
        SchemaType schema_type = TREE;
        string size_units; // B | KB | MB | GB
        OutputType output_type = ASCII;
        string output_path;
    } schema_arguments;

    constexpr string plantuml_string_format = "{0}";

    void get_schema_arguments(cli_arguments_ns::CliArguments* cli_arguments);

    void create_schema(vector<recursive_scan_ns::PlantUMLEntry>& sequence, cli_arguments_ns::CliArguments* cli_arguments);

    string* construct_plantUML_tree_string(const recursive_scan_ns::PlantUMLEntry& entry);

    void create_tree_schema(vector<recursive_scan_ns::PlantUMLEntry>&);
    //void create_box_schema(vector<recursive_scan_ns::PlantUMLEntry>&);
}