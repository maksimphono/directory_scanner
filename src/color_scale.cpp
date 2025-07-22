#include <iostream>
#include <cstdint>
#include <cmath>
#include <cstring>

#include "./include/color_scale.hpp"

using namespace std;

namespace color_scale_ns {
    State state;

    Color size2color(uintmax_t size, State& state = color_scale_ns::state) {
        double dm = state.max_mem_size - state.min_mem_size;
        Color d_color = state.end_color - state.start_color;

        return state.start_color + d_color * ((double)(size - state.min_mem_size) / dm);
    }
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