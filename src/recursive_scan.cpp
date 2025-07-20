#include <iostream>
#include <stack>
#include <vector>
#include <filesystem>

#include "include/recursive_scan.hpp"

namespace fs = filesystem;

namespace recursive_scan_ns {
    vector<FilesystemEntry> plantUML_entries = vector<FilesystemEntry>(); // array that conatins entries of plantUML strings, these will be directly printed to a file, that will be used by plantUML engine

    FilesystemEntry* createFilesystemEntry(uint8_t depth, string name, EntryType type){
        FilesystemEntry* created = new FilesystemEntry;
        created->depth = depth;
        created->name = name;
        created->type = type;

        return created;
    }

    vector<FilesystemEntry>* scan(string& root_path) {
        const fs::path path = fs::path(root_path);

        plantUML_entries.push_back(*createFilesystemEntry(0, path.filename(), DIR)); // first element in the stack is root
        try {
            stack<uint> entries_stack = stack<uint>(); // stack, that will keep track of which directory I'm currently in, each element is an index of that directory in the 'plantUML_entries'
            entries_stack.push(0); // pushing root element

            for (auto entry = fs::recursive_directory_iterator(path); entry != fs::recursive_directory_iterator(); entry++) {
                const fs::path currentPath = entry->path();

                uint8_t depth = entry.depth() + 1; // + 1 because root has depth 0

                if (depth > entries_stack.size()) {
                    // entered a directory
                    cout << "Entering directory " << plantUML_entries[plantUML_entries.size() - 1].name << "\n";
                    entries_stack.push(plantUML_entries.size() - 1); // record index of the parent directory (so the last element in the sequence)
                } else while (depth < entries_stack.size()) {
                    // exiting directory by popping entries from the stack
                    cout << "Exeting directory " << plantUML_entries.at(entries_stack.top()).name << "\n";
                    entries_stack.pop();
                }

                // write current element to the sequence (type = FILE initialy and by default)
                FilesystemEntry* created_entry = createFilesystemEntry(depth, currentPath.filename().string(), FILE);

                if (fs::is_directory(currentPath)) { // if it's a directory
                    created_entry->type = DIR;
                } else if (fs::is_symlink(currentPath)) {
                    created_entry->type = SYMLINK;
                }

                plantUML_entries.push_back(*created_entry);

                // print the top element in the stack
                if (entries_stack.size()) {
                    cout << plantUML_entries[entries_stack.size() - 1].name << " " << entries_stack.size() << endl;
                }
            }
            cout << "Got:\n";
            for (const auto& elem : plantUML_entries) {
                cout << elem.name << " " << elem.type << ":" << (uint)elem.depth << " ";
            }
            return &plantUML_entries;

        } catch (const fs::filesystem_error& e) {
            cerr << "Filesystem error: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "General error: " << e.what() << endl;
        }
        return &plantUML_entries;
    }
}