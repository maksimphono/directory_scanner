#include <iostream>
#include <stack>
#include <filesystem>
using namespace std;

namespace fs = filesystem;

namespace recursive_scan_ns {
    void scan(string& root_path) {
        const fs::path path = fs::path(root_path);

        try {
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                const fs::path currentPath = entry.path();

                if (fs::is_directory(currentPath)) { // if it's a directory
                    cout << "[DIR] " << currentPath.filename().string() << endl;
                }
                else if (fs::is_regular_file(currentPath)) { // if it's a file
                    cout << "[FILE] " << currentPath.filename().string() << endl;
                } else {
                    cout << "[OBJ] " << currentPath.string() << endl;
                }

            }
        } catch (const fs::filesystem_error& e) {
            cerr << "Filesystem error: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "General error: " << e.what() << endl;
        }
    }
}