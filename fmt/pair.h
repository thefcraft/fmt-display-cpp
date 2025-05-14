// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

#include "display.h"
#ifndef FMT_DISPLAY_PAIR_H
#define FMT_DISPLAY_PAIR_H
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
#endif // FMT_DISPLAY_PAIR_H