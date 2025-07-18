#include <format>
#include <iostream>
#include <string>
#include "recursive_scan.cpp"

using namespace recursive_scan_ns;
using namespace std;

namespace plantuml_schema_ns {
    typedef enum {ASCII, JPG, PNG, SVG, PDF} OutputType;
    typedef enum {TREE, BOX} SchemaType;

    OutputType extract_output_file_type(string* output_path) {
        // cout << output_path->substr(output_path->rfind(".") + 1) << endl;
        const string ext = output_path->substr(output_path->rfind(".") + 1);

        if (ext == "jpg" || ext == "jpeg") return JPG;
        if (ext == "png") return PNG;
        if (ext == "svg") return SVG;
        if (ext == "pdf") return PDF;
        return ASCII;
    }

    struct {
        string path;
        SchemaType schema_type = TREE;
        string size_units; // B | KB | MB | GB
        OutputType output_type = ASCII;
        string output_path;
    } schema_arguments;

    auto* get_schema_arguments(auto& cli_arguments) {
        schema_arguments.path = string(*cli_arguments.path);
        schema_arguments.output_path = string(*cli_arguments.output_path);
        schema_arguments.output_type = extract_output_file_type(*cli_arguments.output_path);
        schema_arguments.schema_type = cli_arguments.type == 'b'?BOX:TREE;

        switch (cli_arguments.size_units){
            case 'b': schema_arguments.size_units = "B" ;break;
            case 'k': schema_arguments.size_units = "KB" ;break;
            case 'm': schema_arguments.size_units = "MB" ;break;
            case 'g': schema_arguments.size_units = "GB" ;break;
        }
        cout << "Created schema_arguments: " << schema_arguments.output_type << " " << schema_arguments.size_units << endl;
    }

    void create_schema(vector<PlantUMLEntry>& sequence, auto& cli_arguments) {
        // must create a stream, where the plantuml code will be written, 
        // after that this code will be used within the bash script: "echo $1 | java -jar plantuml -pipe"

        get_schema_arguments(cli_arguments); // creates schema_arguments from cli_arguments

        if (schema_arguments.schema_type == TREE) {
            create_tree_schema(sequence)
        } else if (schema_arguments.schema_type == BOX) {
            create_box_schema(sequence)
        }
    }

    const string plantuml_string_format = "{0}";

    string* construct_plantUML_tree_string(const PlantUMLEntry& entry) {
        static string* plantuml_string = new string();
        //static const char* string_format = "{0} ({1})";

        plantuml_string->assign(entry.depth + 1, '*');
        //*plantuml_string += std::format();
        cout << "QWert";
        //sprintf((char*)plantuml_string->c_str(), plantuml_string_format, );
        //*plantuml_string += format(plantuml_string_format, entry.name);

        return plantuml_string;
    }

    stringstream& create_tree_schema(vector<PlantUMLEntry>& sequence) {
        stringstream plantUML_commands = stringstream();
        string* plantuml_string = new string();

        plantUML_commands << "@startmindmap";

        for (const auto& plantuml_entry : sequence) {
            // TODO: complete this loop, that writes plantuml entries from sequence to the stream
            construct_plantUML_tree_string(plantuml_entry);

            plantUML_commands << plantuml_entry.name;
        }

        plantUML_commands << "@endmindmap";
        return plantUML_commands;
    }
    void create_box_schema(vector<PlantUMLEntry>& sequence) {

    }
}