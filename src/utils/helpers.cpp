#include <string>
#include <cstdint>
#include <cmath>
using namespace std;

string repeat(string str, uint8_t times) { // repeat srting n times
    string result = "";
    for (uint8_t i = 0; i < times; i++) result += str;

    return result;
}

inline double bytes2KB(uintmax_t& bytes_num) { return (double)bytes_num / 10; }

inline double bytes2MB(uintmax_t& bytes_num) { return (double)bytes_num / pow(1024, 2); }

inline double bytes2GB(uintmax_t& bytes_num) { return (double)bytes_num / pow(1024, 3); }

double convert_bytes(uintmax_t& bytes_num, string& units) {
    switch (units[0]) {
        case 'K': return bytes2KB(bytes_num);
        case 'M': return bytes2MB(bytes_num);
        case 'G': return bytes2GB(bytes_num);
        default: return (double)bytes_num;
    }
}