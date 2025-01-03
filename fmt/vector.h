#include "display.h"
#include <vector> // for vector printing


namespace _vector{
    typedef struct State{
        int depth; // curr depth
    } State;

    State state;
    fmt::fmtout fout(&state, sizeof(State));
}


template<typename T>
struct fmt::Display<std::vector<T>> {
    static std::string print(const std::vector<T> &data) {
        fmt::fmtout result;
        result.print('[');
        bool first = true;
        for (const auto& item : data) {
            if (!first) result.print(", ");
            result.print(item);
            first = false;
        }
        result.print(']');
        return result.str();
    }
};

template<typename T>
struct fmt::Display<std::vector<std::vector<T>>> {
    static std::string print(const std::vector<std::vector<T>> &data) {
        _vector::State *state = (_vector::State *)_vector::fout.data;
        _vector::fout.print('[');
        bool first = true;
        for (const auto& item : data) {
            if (!first) _vector::fout.print(",\n");
            if (!first) for (int i = 0; i <= state->depth; i++) _vector::fout.print(" ");
            state->depth++;
            fmt::fout.print(item);
            state->depth--;
            first = false;
        }
        fmt::fout.print(']');
        return fmt::fout.clear_str();
    }
};