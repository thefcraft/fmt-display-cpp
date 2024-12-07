#include "display.h"
#include <map>
template<typename K, typename V>
struct fmt::Display<std::map<K, V>> {
    static std::string print(const std::map<K, V>& map) {
        fmt::fmtout out;
        out << "{";
        bool first = true;
        for (const auto& [key, value] : map) {
            if (!first) out << ", ";
            out << key << ": " << value;
            first = false;
        }
        out << "}";
        return out.str();
    }
};