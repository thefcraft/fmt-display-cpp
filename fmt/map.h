// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

#include "display.h"
#include <map>
#ifndef FMT_DISPLAY_MAP_H
#define FMT_DISPLAY_MAP_H
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
#endif // FMT_DISPLAY_MAP_H