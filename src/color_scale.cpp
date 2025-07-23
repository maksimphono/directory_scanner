#include <iostream>
#include <cstdint>
#include <cmath>
#include <cstring>

#include "./include/color_scale.hpp"

using namespace std;

namespace color_scale_ns {
    State state;

    Color size2color(uintmax_t size, State& state = color_scale_ns::state) {
        if (size > state.max_mem_size) return state.DEFAULT_COLOR;
        double dm = state.max_mem_size - state.min_mem_size;
        Color d_color = state.end_color - state.start_color;

        return state.start_color + d_color * ((double)(size - state.min_mem_size) / dm);
    }
}