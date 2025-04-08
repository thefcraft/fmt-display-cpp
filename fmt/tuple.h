#include "display.h"
#include <tuple>

namespace _tuple{
    template <std::size_t Index = 0, typename... T>
    void print_tuple_elements(fmt::fmtout &fout, const std::tuple<T...>& data) {
        if constexpr (Index < sizeof...(T)) {
            fout << std::get<Index>(data);
            if (Index + 1 < sizeof...(T)) fout << ", ";
            print_tuple_elements<Index + 1>(fout, data); // Recurse for the next index
        }
    }
}

template<typename... T>
struct fmt::Display<std::tuple<T...>> {
    static std::string print(const std::tuple<T...>& data) {
        fmt::fout << "{";
        
        _tuple::print_tuple_elements(fmt::fout, data);

        fmt::fout << "}"; 
        return fmt::fout.clear_str();
    }
};
