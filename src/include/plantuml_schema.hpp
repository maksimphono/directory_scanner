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

    typedef struct {
        string path;
        SchemaType schema_type = TREE;
        bool show_size = false;
        string size_units; // B | KB | MB | GB
        OutputType output_type = ASCII;
        string output_path;
    } SchemaArguments;

    class PlantUMLSchema {
    public:
        virtual ~PlantUMLSchema() {}
        virtual void print(ostream& stream) = 0;
    };

    constexpr string plantuml_string_format = "{0}";

    SchemaArguments& get_schema_arguments(cli_arguments_ns::CliArguments* cli_arguments);

    void create_schema(vector<recursive_scan_ns::FilesystemEntry>& sequence, cli_arguments_ns::CliArguments* cli_arguments, ostream& out_stream = cout);

    string* construct_plantUML_tree_string(const recursive_scan_ns::FilesystemEntry& entry);

    void create_tree_schema(vector<recursive_scan_ns::FilesystemEntry>&, ostream& out_stream = cout);
    void create_box_schema(vector<recursive_scan_ns::FilesystemEntry>&, ostream& out_stream = cout);
}