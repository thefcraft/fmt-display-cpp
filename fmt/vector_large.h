// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

// similar to numpy's printing standards

#include "display.h"
#include <vector> // for vector printing
#ifndef FMT_DISPLAY_VECTOR_LARGE_H
#define FMT_DISPLAY_VECTOR_LARGE_H
namespace _vector_large{
    const int max_print = 6;
    static_assert(max_print > 1, "max_print must be greater than 1");

    typedef struct State{
        int depth = 0; // curr depth
        int mdepth = 0; // max depth
    } State;

    State state;
    fmt::fmtout fout(&state, sizeof(State));
}


template<typename T>
struct fmt::Display<std::vector<T>> {
    static std::string print(const std::vector<T> &data) {
        _vector_large::State *state = (_vector_large::State *)_vector_large::fout.data;
        _vector_large::fout.print('[');
        if (data.size() <= _vector_large::max_print){
            bool first = true;
            for (const auto& item : data) {
                if (!first) {
                    if(state->mdepth == state->depth) _vector_large::fout.print(", ");
                    else {
                        _vector_large::fout.print(",");
                        for (int i = state->depth; i < state->mdepth; i++) _vector_large::fout.print("\n");
                        for (int i = 0; i <= state->depth; i++) _vector_large::fout.print(" ");
                    }
                }
                state->mdepth = (state->mdepth<state->depth)?state->depth:state->mdepth;
                state->depth++; _vector_large::fout.print(item); state->depth--;
                first = false;
            }
        }else{
            state->mdepth = (state->mdepth<state->depth)?state->depth:state->mdepth;
            state->depth++; _vector_large::fout.print(data[0]); state->depth--;
            for (int idx = 1; idx < _vector_large::max_print/2 + _vector_large::max_print%2; idx++){
                if(state->mdepth == state->depth) _vector_large::fout.print(", ");
                else{
                    _vector_large::fout.print(",");
                    for (int i = state->depth; i < state->mdepth; i++) _vector_large::fout.print("\n");
                    for (int i = 0; i <= state->depth; i++) _vector_large::fout.print(" ");
                }
                state->depth++; _vector_large::fout.print(data[idx]); state->depth--;
            }
            // _vector_large::fout.print(",\n\n");
            if(state->mdepth == state->depth) _vector_large::fout.print(", ");
            else{
                _vector_large::fout.print(",");
                for (int i = state->depth; i < state->mdepth; i++) _vector_large::fout.print("\n");
                for (int i = 0; i <= state->depth; i++) _vector_large::fout.print(" ");
            }
            _vector_large::fout.print("...");
            if(state->mdepth == state->depth) _vector_large::fout.print(", ");
            else{
                _vector_large::fout.print(",");
                for (int i = state->depth; i < state->mdepth; i++) _vector_large::fout.print("\n");
                for (int i = 0; i <= state->depth; i++) _vector_large::fout.print(" ");
            }
            state->depth++; _vector_large::fout.print(data[data.size()-_vector_large::max_print/2]); state->depth--;
            for (int idx = data.size()-_vector_large::max_print/2+1; idx < data.size(); idx++){
                if(state->mdepth == state->depth) _vector_large::fout.print(", ");
                else{
                    _vector_large::fout.print(",");
                    for (int i = state->depth; i < state->mdepth; i++) _vector_large::fout.print("\n");
                    for (int i = 0; i <= state->depth; i++) _vector_large::fout.print(" ");
                }
                state->depth++; _vector_large::fout.print(data[idx]); state->depth--;
            }
        }
        
        _vector_large::fout.print(']');
        if (state->depth == 0) state->mdepth = 0; // reseting
        return _vector_large::fout.clear_str();
    }
};
#endif // FMT_DISPLAY_VECTOR_LARGE_H