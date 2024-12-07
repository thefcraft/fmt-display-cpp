// similar to numpy's printing standards

#include "display.h"
#include <vector> // for vector printing

const int max_print = 6;
static_assert(max_print > 1, "max_print must be greater than 1");

template<typename T>
struct fmt::Display<std::vector<T>> {
    static std::string print(const std::vector<T> &data) {
        fmt::fmtout result;
        result.print('[');
        if (data.size() <= max_print){
            bool first = true;
            for (const auto& item : data) {
                if (!first) result.print(", ");
                result.print(item);
                first = false;
            }
        }else{
            result.print(data[0]);
            for (int idx = 1; idx < max_print/2 + max_print%2; idx++){
                result.print(", ");
                result.print(data[idx]);
            }
            result.print(", ");
            result.print("...");
            for (int idx = data.size()-max_print/2; idx < data.size(); idx++){
                result.print(", ");
                result.print(data[idx]);
            }
        }
        result.print(']');
        return result.str();
    }
};

template<typename T>
struct fmt::Display<std::vector<std::vector<T>>> {
    static std::string print(const std::vector<std::vector<T>> &data) {
        fmt::fout.print('[');
        if (data.size() <= max_print){
            bool first = true;
            for (const auto& item : data) {
                if (!first) fmt::fout.print(",");
                if (!first) for (int i = fmt::fout.depth; i <= fmt::fout.mdepth; i++) fmt::fout.print("\n");
                if (!first) for (int i = 0; i <= fmt::fout.depth; i++) fmt::fout.print(" ");
                fmt::fout.mdepth = (fmt::fout.mdepth<fmt::fout.depth)?fmt::fout.depth:fmt::fout.mdepth;
                fmt::fout.depth++; fmt::fout.print(item); fmt::fout.depth--;
                first = false;
            }
        }else{
            fmt::fout.depth++; fmt::fout.print(data[0]); fmt::fout.depth--;

            fmt::fout.mdepth = (fmt::fout.mdepth<fmt::fout.depth)?fmt::fout.depth:fmt::fout.mdepth;

            for (int idx = 1; idx < max_print/2 + max_print%2; idx++){
                fmt::fout.print(",");
                for (int i = fmt::fout.depth; i <= fmt::fout.mdepth; i++) fmt::fout.print("\n");
                for (int i = 0; i <= fmt::fout.depth; i++) fmt::fout.print(" ");
                fmt::fout.depth++; fmt::fout.print(data[idx]); fmt::fout.depth--;
            }
            // fmt::fout.print(",\n\n");
            fmt::fout.print(",");
            for (int i = fmt::fout.depth; i <= fmt::fout.mdepth; i++) fmt::fout.print("\n");
            for (int i = 0; i <= fmt::fout.depth; i++) fmt::fout.print(" ");
            fmt::fout.print("...");
            fmt::fout.print(",");
            for (int i = fmt::fout.depth; i <= fmt::fout.mdepth; i++) fmt::fout.print("\n");
            for (int i = 0; i <= fmt::fout.depth; i++) fmt::fout.print(" ");
            fmt::fout.depth++; fmt::fout.print(data[data.size()-max_print/2]); fmt::fout.depth--;
            for (int idx = data.size()-max_print/2+1; idx < data.size(); idx++){
                fmt::fout.print(",");
                for (int i = fmt::fout.depth; i <= fmt::fout.mdepth; i++) fmt::fout.print("\n");
                for (int i = 0; i <= fmt::fout.depth; i++) fmt::fout.print(" ");
                fmt::fout.depth++; fmt::fout.print(data[idx]); fmt::fout.depth--;
            }
        }
        fmt::fout.print(']');
        if (fmt::fout.depth == 0) fmt::fout.mdepth = 0;
        return fmt::fout.clear_str();
    }
};