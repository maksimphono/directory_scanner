#include <iostream>
#include <cstdint>
#include <vector>
#include <cmath>
#include <string.h>
using namespace std;

namespace color_scale_ns {
    enum {R, G, B};

    class Color {
    private:
        uint8_t vector_rgb[3] = {0, 0, 0};
    public:
        Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) {
            this->vector_rgb[R] = r;
            this->vector_rgb[G] = g;
            this->vector_rgb[B] = b;
        }
        Color(Color* another) {
            memcpy(this->vector_rgb, another->vector_rgb, sizeof(another->vector_rgb));
        }
        string str() {
            char* buf = new char[8];

            sprintf(buf, "#%02x%02x%02x", this->vector_rgb[R], this->vector_rgb[G], this->vector_rgb[B]);
            buf[7] = '\0';

            string s = string(buf);

            delete buf;
            return s;
        }
        const uint8_t* rgb() {
            return (const uint8_t*)this->vector_rgb;
        }
        double length() {
            double result = 0;

            for (uint8_t i = 0; i < 3; i++)
                result += pow(this->rgb()[i], 2);

            return sqrt(result);
        }
        const uint8_t operator[] (uint8_t i){
            return this->rgb()[i];
        }
        Color operator+ (Color& another){
            Color new_color = Color(this);

            for (uint8_t i = 0; i < 3; i++)
                new_color.vector_rgb[i] += another.rgb()[i];

            return new_color;
        }
        Color operator (Color& another){
            Color new_color = Color(this);

            for (uint8_t i = 0; i < 3; i++)
                new_color.vector_rgb[i] += another.rgb()[i];

            return new_color;
        } 
        Color operator* (double c) {
            Color new_color = Color(this);

            for (uint8_t i = 0; i < 3; i++)
                new_color.vector_rgb[i] = (uint8_t)((double)new_color.vector_rgb[i] * c);

            return new_color;
        }
    };

    typedef struct {
        uintmax_t max_mem_size = 0;
        uintmax_t min_mem_size = 0;
    } State;
    State state;

    Color convert_to_color() {

    }
}

using namespace color_scale_ns;
int main() {
    Color c1 = Color(2,3,4);
    Color c2 = Color(1,1,1);
    c1 = c1 + c2;
    cout << c1.str();
    return 0;
}