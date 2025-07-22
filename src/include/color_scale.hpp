#include <iostream>
#include <cstdint>
#include <cmath>
#include <cstring>
using namespace std;

namespace color_scale_ns {
    enum {R, G, B};

    class Color {
    private:
        int16_t vector_rgb[3] = {0, 0, 0};
    public:
        Color(int16_t r = 0, int16_t g = 0, int16_t b = 0) {
            this->vector_rgb[R] = r;
            this->vector_rgb[G] = g;
            this->vector_rgb[B] = b;
        }
        Color(Color* another) {
            memcpy(this->vector_rgb, another->vector_rgb, sizeof(another->vector_rgb));
        }
        Color(string s) {
            int r = 0, g = 0, b = 0;
            sscanf(s.c_str(), "#%2x%2x%2x", &r, &g, &b);

            this->vector_rgb[R] = (int16_t)r;
            this->vector_rgb[G] = (int16_t)g;
            this->vector_rgb[B] = (int16_t)b;
        }
        string str() {
            if (this->rgb()[R] < 0 || this->rgb()[G] < 0 || this->rgb()[B] < 0) return string("#000000");

            char* buf = new char[8];

            sprintf(buf, "#%02x%02x%02x", this->rgb()[R], this->rgb()[G], this->rgb()[B]);
            buf[7] = '\0';

            string s = string(buf);

            delete buf;
            return s;
        }
        const int16_t* rgb() {
            return (const int16_t*)this->vector_rgb;
        }
        double length() {
            double result = 0;

            for (uint8_t i = 0; i < 3; i++)
                result += pow(this->rgb()[i], 2);

            return sqrt(result);
        }
        const int16_t operator[] (uint8_t i){
            return this->rgb()[i];
        }
        Color operator+ (Color another){
            Color new_color = Color(this);

            for (uint8_t i = 0; i < 3; i++)
                new_color.vector_rgb[i] += another.rgb()[i];

            return new_color;
        }
        Color operator- (Color another){
            Color new_color = Color(this);

            for (uint8_t i = 0; i < 3; i++)
                new_color.vector_rgb[i] -= another.rgb()[i];

            return new_color;
        } 
        Color operator* (double c) {
            Color new_color = Color(this);

            for (uint8_t i = 0; i < 3; i++)
                new_color.vector_rgb[i] = (int16_t)((double)new_color.vector_rgb[i] * c);

            return new_color;
        }
    };

    typedef struct {
        uintmax_t max_mem_size = 0;
        uintmax_t min_mem_size = 0;
        Color start_color;
        Color end_color;
    } State;

    Color size2color(uintmax_t size, State& state);
}

/*
using namespace color_scale_ns;
int main() {
    Color c1 = Color(2,3,4);
    Color c2 = Color(1,2,3);
    c2 = size2color(70);
    c1 = (c1 - c2);
    cout << Color("#ff0465").str();
    //printf("#%d %d %d", c2.rgb()[0], c2.rgb()[1], c2.rgb()[2]);
    return 0;
}
*/