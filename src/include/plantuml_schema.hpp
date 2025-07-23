#pragma once

#include <format>
#include <iostream>
#include <string>

#include "recursive_scan.hpp"
#include "cli_arguments.hpp"
#include "color_scale.hpp"

using namespace std;
//using namespace recursive_scan_ns;
using namespace color_scale_ns;
typedef color_scale_ns::State ColorScaleState;

namespace plantuml_schema_ns {
    typedef enum {ASCII, JPG, PNG, SVG, PDF} OutputType;
    typedef enum {TREE, BOX} SchemaType;
    enum {start, end};

    OutputType extract_output_file_type(string* output_path);

    typedef struct {
        string path;
        SchemaType schema_type = TREE;
        bool show_size = false;
        string size_units; // B | KB | MB | GB
        bool show_color = false;
        ColorScaleState color_state;
        OutputType output_type = ASCII;
    } SchemaArguments;

    class PlantUMLSchema_abstract {
    public:
        string default_format = "{0}";
        virtual ~PlantUMLSchema_abstract() {}
        virtual void print(ostream& stream) = 0;
    };
    class PlantUMLSchema : public PlantUMLSchema_abstract {
    public:
        void print(ostream& stream) override {return;}
    };

    string create_color_string(recursive_scan_ns::FilesystemEntry& entry, ColorScaleState& color_state, string& format_color);

    SchemaArguments& get_schema_arguments(cli_arguments_ns::CliArguments& cli_arguments);

    void create_schema(vector<recursive_scan_ns::FilesystemEntry>& sequence, cli_arguments_ns::CliArguments& cli_arguments, ostream& out_stream = cout);

    string* construct_plantUML_tree_string(const recursive_scan_ns::FilesystemEntry& entry);

    void create_tree_schema(vector<recursive_scan_ns::FilesystemEntry>&, ostream& out_stream = cout);
    void create_box_schema(vector<recursive_scan_ns::FilesystemEntry>&, ostream& out_stream = cout);
}