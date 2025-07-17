#include <iostream>
#include <stack>
#include <vector>
#include <filesystem>
using namespace std;

namespace fs = filesystem;

namespace recursive_scan_ns {
    typedef struct {
        uint8_t depth;
        string name;
    } PlantUMLEntry;

    PlantUMLEntry* createPlantUMLEntry(uint8_t depth, string name){
        PlantUMLEntry* created = new PlantUMLEntry;
        created->depth = depth;
        created->name = name;

        return created;
    }

    vector<PlantUMLEntry> plantUML_entries = vector<PlantUMLEntry>(); // array that conatins entries of plantUML strings, these will be directly printed to a file, that will be used by plantUML engine

    vector<PlantUMLEntry>* scan(string& root_path) {
        const fs::path path = fs::path(root_path);

        plantUML_entries.push_back(*createPlantUMLEntry(0, path.filename())); // first element in the stack is root
        try {
            stack<int> entries_stack = stack<int>(); // stack, that will keep track of which directory I'm currently in, each element is an index of that directory in the 'plantUML_entries'
            entries_stack.push(0); // pushing root element

            for (auto entry = fs::recursive_directory_iterator(path); entry != fs::recursive_directory_iterator(); entry++) {
                const fs::path currentPath = entry->path();

                uint depth = entry.depth() + 1; // + 1 because root has depth 0

                if (depth > entries_stack.size()) {
                    // entered a directory
                    cout << "Entering directory " << plantUML_entries[plantUML_entries.size() - 1].name << "\n";
                    entries_stack.push(plantUML_entries.size() - 1); // record index of the parent directory (so the last element in the sequence)
                } else while (depth < entries_stack.size()) {
                    cout << "Exeting directory " << plantUML_entries.at(entries_stack.top()).name << "\n";
                    entries_stack.pop();
                }
                // write current element to the sequence
                PlantUMLEntry* created_entry = createPlantUMLEntry(depth, currentPath.filename().string());
                plantUML_entries.push_back(*created_entry);

                // print the top element in the stack
                if (entries_stack.size()) {
                    cout << plantUML_entries[entries_stack.size() - 1].name << " " << entries_stack.size() << endl;
                }

                if (fs::is_directory(currentPath)) { // if it's a directory
                    cout << "[DIR] " << currentPath.filename().string() << " " << entry.depth() << endl;
                }
                else if (fs::is_regular_file(currentPath)) { // if it's a file
                    cout << "[FILE] " << currentPath.filename().string() << " " << entry.depth() << endl;
                } else {
                    cout << "[OBJ] " << currentPath.string() << " " << entry.depth() << endl;
                }

                cout << "Got:\n";
                for (const auto& elem : plantUML_entries) {
                    cout << elem.name << " ";
                }
            }
            return &plantUML_entries;

        } catch (const fs::filesystem_error& e) {
            cerr << "Filesystem error: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "General error: " << e.what() << endl;
        }
    }
}