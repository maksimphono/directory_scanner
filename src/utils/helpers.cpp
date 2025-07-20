#include <string>
#include <cstdint>
using namespace std;

string repeat(string str, uint8_t times) { // repeat srting n times
    string result = "";
    for (uint8_t i = 0; i < times; i++) result += str;

    return result;
}
