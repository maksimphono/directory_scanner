#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <filesystem>

using namespace std;

typedef unsigned int uint;

namespace fs = filesystem;

namespace recursive_scan_ns {
    typedef char EntryType;
    const EntryType FILE = 'f', DIR = 'd', SYMLINK = 'l', FIFO = 'p';

    typedef struct {
        uint8_t depth;
        string name;
        uintmax_t size;
        EntryType type;
    } FilesystemEntry;

    FilesystemEntry* createFilesystemEntry(uint8_t depth, string name, EntryType type = FILE, uintmax_t size = 0);
    
    vector<FilesystemEntry>& scan(string& root_path);
}