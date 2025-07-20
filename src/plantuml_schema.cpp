#include <format>
#include <iostream>
#include <string>

#include "include/plantuml_schema.hpp"
#include "utils/helpers.cpp"

//using namespace ;
using namespace std;

namespace plantuml_schema_ns {

    class PlantUML_TreeSchema : public PlantUMLSchema {
    private:
        string string_format;
        vector<recursive_scan_ns::FilesystemEntry>& sequence;
    public:
        PlantUML_TreeSchema(vector<recursive_scan_ns::FilesystemEntry>& sequence) : sequence(sequence) {
            this->string_format = "{0}";
            // TODO: create format based on the schema_arguments

            // here must be logic, that creates format for each created string
            // and gather overall informationfrom the sequence of entries
            if (schema_arguments.show_size) {
                this->string_format = "{0} ({1})";
            }
        }
        string construct_plantUML_string(const recursive_scan_ns::FilesystemEntry& entry) {
            string plantuml_string = string();

            plantuml_string.assign(entry.depth + 1, '*');
            plantuml_string += " ";
            plantuml_string += vformat(this->string_format, make_format_args(entry.name, schema_arguments.size_units)); // was forced to do so, using regular std::format the same way as in the documentation (https://en.cppreference.com/w/cpp/utility/format/format.html) produce error "...`string_format` is not a constant expression...", idk why

            return plantuml_string;
        }
        void print(ostream& stream) override {
            // will output entire plantuml code into the provided stream
            stream << "@startmindmap\n";

            for (const auto& plantuml_entry : this->sequence) {
                stream
                    << this->construct_plantUML_string(plantuml_entry)
                    << endl;
            }

            stream << "@endmindmap\n";
        }
    };

    class PlantUML_BoxSchema : public PlantUMLSchema {
    private:
        string string_format;
        vector<recursive_scan_ns::FilesystemEntry>& sequence;
    public:
        PlantUML_BoxSchema(vector<recursive_scan_ns::FilesystemEntry>& sequence) : sequence(sequence) {
            this->string_format = "state \"{1}\" as S{0}";
            // TODO: create format based on the schema_arguments

            if (schema_arguments.show_size)
                this->string_format = "state \"{1} ({2} {3})\" as S{0}";
            // here must be logic, that creates format for each created string
            // and gather overall informationfrom the sequence of entries
        }
        string construct_plantUML_string(uint8_t index, recursive_scan_ns::FilesystemEntry& entry) {
            return vformat(this->string_format, make_format_args(index, entry.name, entry.size, schema_arguments.size_units));
        }
        void print(ostream& stream) override {
            stream << "@startuml\n";

            recursive_scan_ns::FilesystemEntry root = this->sequence.front();
            stream << this->construct_plantUML_string(0, root);
            uint8_t diff = 0;

            for (uint8_t i = 1; i < this->sequence.size(); i++) {
                recursive_scan_ns::FilesystemEntry& current_entry = this->sequence[i];
                recursive_scan_ns::FilesystemEntry& prev_entry = this->sequence[i - 1];

                if (current_entry.depth > prev_entry.depth)
                    // enring a directory
                    stream << "{" << endl;
                else if (current_entry.depth < prev_entry.depth) {
                    // exiting a directory
                    diff = prev_entry.depth - current_entry.depth;
                    stream 
                        << endl
                        << repeat("}\n", diff);
                } else {
                    // in the same directory
                    stream << endl;
                }

                stream << this->construct_plantUML_string(i, current_entry);
            }
            stream
                << endl
                << repeat("}\n", this->sequence.back().depth);

            stream << "@enduml\n";
        }
    };

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

    void get_schema_arguments(cli_arguments_ns::CliArguments* cli_arguments) {
        schema_arguments.path = string(*cli_arguments->path);

        if (cli_arguments->output_path != nullptr) {
            schema_arguments.output_path = string(*cli_arguments->output_path);
            schema_arguments.output_type = extract_output_file_type(cli_arguments->output_path);
        } else {
            schema_arguments.output_type = ASCII;
        }

        if (cli_arguments->size_units != '\0') {
            schema_arguments.show_size = true;
        } else
            schema_arguments.show_size = false;

        schema_arguments.schema_type = cli_arguments->type == 'b'?BOX:TREE;
        
        switch (cli_arguments->size_units) {
            case 'b': schema_arguments.size_units = "B" ;break;
            case 'k': schema_arguments.size_units = "KB" ;break;
            case 'm': schema_arguments.size_units = "MB" ;break;
            case 'g': schema_arguments.size_units = "GB" ;break;
        }
        cout << "Created schema_arguments: " << schema_arguments.output_type << " " << schema_arguments.size_units << endl;
    }

    void create_schema(vector<recursive_scan_ns::FilesystemEntry>& sequence, cli_arguments_ns::CliArguments* cli_arguments, ostream& out_stream) {
        // must create a stream, where the plantuml code will be written, 
        // after that this code will be used within the bash script: "echo $1 | java -jar plantuml -pipe"
        get_schema_arguments(cli_arguments); // creates schema_arguments from cli_arguments

        switch (schema_arguments.schema_type) {
            case TREE: create_tree_schema(sequence, out_stream); break;
            case BOX: create_box_schema(sequence, out_stream); break;
        }
    }

    void create_tree_schema(vector<recursive_scan_ns::FilesystemEntry>& sequence, ostream& out_stream) {
        PlantUML_TreeSchema schema = PlantUML_TreeSchema(sequence);
        schema.print(out_stream);
    }

    void create_box_schema(vector<recursive_scan_ns::FilesystemEntry>& sequence, ostream& out_stream) {
        PlantUML_BoxSchema schema = PlantUML_BoxSchema(sequence);
        schema.print(out_stream);
    }
}