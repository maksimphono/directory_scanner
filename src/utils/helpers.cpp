#include <string>
#include <cstdint>
#include <filesystem>
#include <cmath>
using namespace std;

string repeat(string str, uint8_t times) { // repeat srting n times
    string result = "";
    for (uint8_t i = 0; i < times; i++) result += str;

    return result;
}

inline double bytes2KB(uintmax_t& bytes_num) { return bytes_num / 1024; }

inline double bytes2MB(uintmax_t& bytes_num) { return bytes_num / pow(1024, 2); }

inline double bytes2GB(uintmax_t& bytes_num) { return bytes_num / pow(1024, 3); }