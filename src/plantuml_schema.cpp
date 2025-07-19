#include <format>
#include <iostream>
#include <string>

#include "include/plantuml_schema.hpp"

//using namespace ;
using namespace std;

namespace plantuml_schema_ns {
    OutputType extract_output_file_type(string* output_path) {
        // cout << output_path->substr(output_path->rfind(".") + 1) << endl;
        if (output_path == nullptr) return ASCII;

        string ext = output_path->substr(output_path->rfind(".") + 1);

        if (ext == "jpg" || ext == "jpeg") return JPG;
        if (ext == "png") return PNG;
        if (ext == "svg") return SVG;
        if (ext == "pdf") return PDF;
        return ASCII;
    }

    // TODO: create a way of defining format of resulting PlantUML string in advance
    string* create_plantuml_string_format() {

    }
    void get_schema_arguments(cli_arguments_ns::CliArguments* cli_arguments) {
        schema_arguments.path = string(*cli_arguments->path);

        if (cli_arguments->output_path != nullptr) {
            schema_arguments.output_path = string(*cli_arguments->output_path);
            schema_arguments.output_type = extract_output_file_type(cli_arguments->output_path);
        } else {
            schema_arguments.output_type = ASCII;
        }
        schema_arguments.schema_type = cli_arguments->type == 'b'?BOX:TREE;
        
        switch (cli_arguments->size_units) {
            case 'b': schema_arguments.size_units = "B" ;break;
            case 'k': schema_arguments.size_units = "KB" ;break;
            case 'm': schema_arguments.size_units = "MB" ;break;
            case 'g': schema_arguments.size_units = "GB" ;break;
        }
        cout << "Created schema_arguments: " << schema_arguments.output_type << " " << schema_arguments.size_units << endl;
    }

    void create_schema(vector<recursive_scan_ns::PlantUMLEntry>& sequence, cli_arguments_ns::CliArguments* cli_arguments) {
        // must create a stream, where the plantuml code will be written, 
        // after that this code will be used within the bash script: "echo $1 | java -jar plantuml -pipe"
        get_schema_arguments(cli_arguments); // creates schema_arguments from cli_arguments

        if (schema_arguments.schema_type == TREE) {
            create_tree_schema(sequence);
        } else if (schema_arguments.schema_type == BOX) {
            //create_box_schema(sequence);
        }
    }

    string* construct_plantUML_tree_string(const recursive_scan_ns::PlantUMLEntry& entry) {
        static string* plantuml_string = new string();

        plantuml_string->assign(entry.depth + 1, '*');
        *plantuml_string += " ";
        *plantuml_string += format(plantuml_string_format, entry.name, entry.type);

        return plantuml_string;
    }

    void create_tree_schema(vector<recursive_scan_ns::PlantUMLEntry>& sequence) {
        stringstream* plantUML_commands = new stringstream();
        string* plantuml_string = nullptr;

        *plantUML_commands << "@startmindmap\n";

        for (const auto& plantuml_entry : sequence) {
            // TODO: complete this loop, that writes plantuml entries from sequence to the stream
            plantuml_string = construct_plantUML_tree_string(plantuml_entry);

            *plantUML_commands << *plantuml_string << endl;
        }

        *plantUML_commands << "@endmindmap\n";

        cout << plantUML_commands->str();

        delete plantUML_commands;
        delete plantuml_string;
    }
}