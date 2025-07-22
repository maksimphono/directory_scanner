#include <format>
#include <iostream>
#include <string>

#include "include/plantuml_schema.hpp"
#include "utils/helpers.cpp"

//using namespace ;
using namespace std;

namespace plantuml_schema_ns {
    SchemaArguments schema_arguments;

    class PlantUML_TreeSchema : public PlantUMLSchema {
    private:
        SchemaArguments& _schema_arguments = plantuml_schema_ns::schema_arguments;
        struct {
            string color = "";
            string size_int = "";
            string size_float = "";
            string name = "{0}";
        } string_format;
        vector<recursive_scan_ns::FilesystemEntry>& sequence;
    public:
        PlantUML_TreeSchema(vector<recursive_scan_ns::FilesystemEntry>& sequence) : sequence(sequence) {
            // here must be logic, that creates format for each created string
            // and gather overall informationfrom the sequence of entries
            if (this->_schema_arguments.show_color) {
                this->string_format.color = "[{0}]";
            }
            if (this->_schema_arguments.show_size) {
                if (this->_schema_arguments.size_units == "B")
                    this->string_format.size_int = "({0} {1})";
                else
                    this->string_format.size_float = "({0:.2f} {1})";
            }
        }
        string format_entry(recursive_scan_ns::FilesystemEntry& entry) {
            string result = "";
            string ada = "#adaada";

            if (this->_schema_arguments.show_color) {
                result += vformat(this->string_format.color, make_format_args(ada)); // was forced to do so, using regular std::format the same way as in the documentation (https://en.cppreference.com/w/cpp/utility/format/format.html) produce error "...`string_format` is not a constant expression...", idk why
            }
            result += " ";
            result += vformat(this->string_format.name, make_format_args(entry.name));
            result += " ";
            if (this->_schema_arguments.show_size) {
                if (entry.size != 0) {
                    if (this->_schema_arguments.size_units == "B") {
                        result += vformat(this->string_format.size_int, make_format_args(entry.size, this->_schema_arguments.size_units));
                    } else {
                        double converted_size = convert_bytes(entry.size, this->_schema_arguments.size_units);
                        result += vformat(this->string_format.size_float, make_format_args(converted_size, this->_schema_arguments.size_units));
                    }
                }
            }
            return result;
        }
        string construct_plantUML_string(recursive_scan_ns::FilesystemEntry& entry) {
            string plantuml_string = string();

            plantuml_string += repeat("*", entry.depth + 1);
            plantuml_string += this->format_entry(entry);

            return plantuml_string;
        }
        void print(ostream& stream) override {
            // will output entire plantuml code into the provided stream
            stream << "@startmindmap\n";

            for (auto& plantuml_entry : this->sequence) {
                stream
                    << this->construct_plantUML_string(plantuml_entry)
                    << endl;
            }

            stream << "@endmindmap\n";
        }
    };

    class PlantUML_BoxSchema : public PlantUMLSchema {
    private:
        SchemaArguments& _schema_arguments = plantuml_schema_ns::schema_arguments;
        struct {
            string color = "";
            string size = "";
            string name = "{1}";
            string index = "as S{0}";
        } string_format;
        vector<recursive_scan_ns::FilesystemEntry>& sequence;
    public:
        PlantUML_BoxSchema(vector<recursive_scan_ns::FilesystemEntry>& sequence) : sequence(sequence) {
            this->string_format.name = "\"{0}\"";

            if (this->_schema_arguments.show_color) {
                this->string_format.color = "{0}";
            }
            if (this->_schema_arguments.show_size) {
                this->string_format.name = "\"{0}";
                if (this->_schema_arguments.size_units == "B")
                    this->string_format.size = "({0} {1})";
                else
                    this->string_format.size = "({0:.2f} {1})";
            }
            // here must be logic, that creates format for each created string
            // and gather overall informationfrom the sequence of entries
        }
        string construct_plantUML_string(uint8_t index, recursive_scan_ns::FilesystemEntry& entry) {
            string result = "state ";

            result += vformat(this->string_format.name, make_format_args(entry.name));

            if (this->_schema_arguments.show_size) {
                if (entry.size != 0) {
                    result += " ";
                    if (this->_schema_arguments.size_units == "B") {
                        result += vformat(this->string_format.size, make_format_args(entry.size, this->_schema_arguments.size_units)); // was forced to do so, using regular std::format the same way as in the documentation (https://en.cppreference.com/w/cpp/utility/format/format.html) produce error "...`string_format` is not a constant expression...", idk why
                    } else {
                        double converted_size = convert_bytes(entry.size, this->_schema_arguments.size_units);
                        result += vformat(this->string_format.size, make_format_args(converted_size, this->_schema_arguments.size_units));
                    }
                }
                result += "\"";
            }

            result += " ";
            result += vformat(this->string_format.index, make_format_args(index));
            result += " ";

            if (this->_schema_arguments.show_color) {
                result += vformat(this->string_format.color, make_format_args("#afdaed"));
            }

            return result;
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

    SchemaArguments& get_schema_arguments(cli_arguments_ns::CliArguments& cli_arguments, vector<recursive_scan_ns::FilesystemEntry>& sequence) {
        SchemaArguments& schema_arguments = plantuml_schema_ns::schema_arguments;
        schema_arguments.path = string(*cli_arguments.path);

        if (cli_arguments.output_path != nullptr) {
            //schema_arguments.output_path = string(*cli_arguments.output_path);
            schema_arguments.output_type = extract_output_file_type(cli_arguments.output_path);
        } else {
            schema_arguments.output_type = ASCII;
        }

        if (cli_arguments.size_units != '\0') {
            schema_arguments.show_size = true;
        } else
            schema_arguments.show_size = false;

        schema_arguments.schema_type = cli_arguments.type == 'b'?BOX:TREE;

        switch (cli_arguments.size_units) {
            case 'b': schema_arguments.size_units = "B" ;break;
            case 'k': schema_arguments.size_units = "KB" ;break;
            case 'm': schema_arguments.size_units = "MB" ;break;
            case 'g': schema_arguments.size_units = "GB" ;break;
        }

        if (cli_arguments.start_color != "" && cli_arguments.end_color != "") {
            uintmax_t min_mem_size = SIZE_MAX;
            uintmax_t max_mem_size = 0;

            schema_arguments.show_color = true;
            schema_arguments.color_state.start_color = Color(cli_arguments.start_color);
            schema_arguments.color_state.end_color = Color(cli_arguments.end_color);

            for (const auto& entry : sequence) {
                if (entry.size > max_mem_size) max_mem_size = entry.size;
                else if (entry.size < min_mem_size) min_mem_size = entry.size;
            }

            schema_arguments.color_state.min_mem_size = min_mem_size;
            schema_arguments.color_state.max_mem_size = max_mem_size;

            cout << "Color state: " << schema_arguments.color_state.min_mem_size << schema_arguments.color_state.max_mem_size << schema_arguments.color_state.start_color.str() << schema_arguments.color_state.end_color.str() << endl;
        }
        cout << "Created schema_arguments: " << schema_arguments.output_type << " " << schema_arguments.size_units << endl;

        return schema_arguments;
    }

    void create_schema(vector<recursive_scan_ns::FilesystemEntry>& sequence, cli_arguments_ns::CliArguments& cli_arguments, ostream& out_stream) {
        // must create a stream, where the plantuml code will be written, 
        // after that this code will be used within the bash script: "echo $1 | java -jar plantuml -pipe"
        SchemaArguments& schema_arguments = get_schema_arguments(cli_arguments, sequence); // creates schema_arguments from cli_arguments
        PlantUMLSchema* schema = nullptr;

        switch (schema_arguments.schema_type) {
            case TREE: schema = new PlantUML_TreeSchema(sequence); break;
            case BOX: schema = new PlantUML_BoxSchema(sequence); break;
        }

        if (schema != nullptr)
            schema->print(out_stream);

        delete schema;
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