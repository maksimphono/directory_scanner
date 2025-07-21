#include <iostream>
#include <stack>
#include <vector>
#include <filesystem>

#include "include/recursive_scan.hpp"

namespace fs = filesystem;

namespace recursive_scan_ns {
    vector<FilesystemEntry> filesystem_entries = vector<FilesystemEntry>(); // array that conatins entries of plantUML strings, these will be directly printed to a file, that will be used by plantUML engine

    FilesystemEntry* createFilesystemEntry(uint8_t depth, string name, EntryType type, uintmax_t size) {
        FilesystemEntry* created = new FilesystemEntry;
        created->depth = depth;
        created->name = name;
        created->type = type;
        created->size = size;
        cout << "Size: " << size << endl;

        return created;
    }

    vector<FilesystemEntry>* scan(string& root_path) {
        const fs::path path = fs::path(root_path);
        uintmax_t top_entry_size = 0;
        vector<FilesystemEntry>& filesystem_entries = recursive_scan_ns::filesystem_entries;

        filesystem_entries.push_back(*createFilesystemEntry(0, path.filename(), DIR)); // first element in the stack is root
        try {
            stack<uint> entries_stack = stack<uint>(); // stack, that will keep track of which directory I'm currently in, each element is an index of that directory in the 'filesystem_entries'
            entries_stack.push(0); // pushing root element

            for (auto entry = fs::recursive_directory_iterator(path); entry != fs::recursive_directory_iterator(); entry++) {
                const fs::path currentPath = entry->path();

                uint8_t depth = entry.depth() + 1; // + 1 because root has depth 0

                // write current element to the sequence (type = FILE initialy and by default)
                FilesystemEntry* created_entry = createFilesystemEntry(depth, currentPath.filename().string(), FILE);

                if (depth > entries_stack.size()) {
                    // entered a directory
                    cout << "Entering directory " << filesystem_entries[filesystem_entries.size() - 1].name << "\n";
                    entries_stack.push(filesystem_entries.size() - 1); // record index of the parent directory (so the last element in the sequence)
                } else while (depth < entries_stack.size()) {
                    // exiting directory by popping entries from the stack
                    cout << "Exeting directory " << filesystem_entries.at(entries_stack.top()).name << "\n";
                    top_entry_size = filesystem_entries[entries_stack.top()].size;
                    entries_stack.pop();
                    filesystem_entries[entries_stack.top()].size += top_entry_size;
                }

                if (fs::is_directory(currentPath)) { // if it's a directory
                    created_entry->type = DIR;
                } else if (fs::is_symlink(currentPath)) {
                    created_entry->type = SYMLINK;
                } else if (fs::is_regular_file(currentPath)) {
                    created_entry->type = FILE;
                    created_entry->size = fs::file_size(currentPath);
                    filesystem_entries[entries_stack.top()].size += created_entry->size;
                }

                filesystem_entries.push_back(*created_entry);
                // print the top element in the stack
                if (entries_stack.size()) {
                    cout << filesystem_entries[entries_stack.size() - 1].name << " " << entries_stack.size() << endl;
                }
            }

            while (1 < entries_stack.size()) {
                // exiting directory by popping entries from the stack
                cout << "Exeting directory " << filesystem_entries.at(entries_stack.top()).name << "\n";
                top_entry_size = filesystem_entries[entries_stack.top()].size;
                entries_stack.pop();
                filesystem_entries[entries_stack.top()].size += top_entry_size;
            }

            //filesystem_entries[0].size += filesystem_entries[entries_stack.top()].size;
            cout << "Got:\n";
            for (const auto& elem : filesystem_entries) {
                cout << elem.name << " " << elem.type << ":" << (uint)elem.depth << " ";
            }
            return &filesystem_entries;

        } catch (const fs::filesystem_error& e) {
            cerr << "Filesystem error: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "General error: " << e.what() << endl;
        }
        return &filesystem_entries;
    }
}