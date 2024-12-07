#include "display.h"
#include <set>
template<typename T>
struct fmt::Display<std::set<T>> {
    static std::string print(const std::set<T>& set) {
        fmtout out;
        out << "{";
        bool first = true;
        for (const auto& value : set) {
            if (!first) out << ", ";
            out << value;
            first = false;
        }
        out << "}";
        return out.str();
    }
};