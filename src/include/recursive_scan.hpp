#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <filesystem>

using namespace std;

namespace fs = filesystem;

namespace recursive_scan_ns {
    typedef char EntryType;
    const EntryType FILE = 'f', DIR = 'd', SYMLINK = 'l', FIFO = 'p';

    typedef struct {
        uint8_t depth;
        string name;
        EntryType type;
    } PlantUMLEntry;

    PlantUMLEntry* createPlantUMLEntry(uint8_t depth, string name, EntryType type = FILE);
    
    vector<PlantUMLEntry>* scan(string& root_path);
}