#include "display.h"
#include <vector> // for vector printing
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
        fmt::fout.print('[');
        bool first = true;
        for (const auto& item : data) {
            if (!first) fmt::fout.print(",\n");
            if (!first) for (int i = 0; i <= fmt::fout.depth; i++) fmt::fout.print(" ");
            fmt::fout.depth++;
            fmt::fout.print(item);
            fmt::fout.depth--;
            first = false;
        }
        fmt::fout.print(']');
        return fmt::fout.clear_str();
    }
};