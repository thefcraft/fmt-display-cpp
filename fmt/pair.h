#include "display.h"
template<typename T, typename V>
struct fmt::Display<std::pair<T, V>> {
    static std::string print(const std::pair<T, V>& pair) {
        fmtout out;
        out << "{";
        out << pair.first << ", " << pair.second;
        out << "}";
        return out.str();
    }
};