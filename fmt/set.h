// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

#include "display.h"
#include <set>
#ifndef FMT_DISPLAY_SET_H
#define FMT_DISPLAY_SET_H
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
#endif // FMT_DISPLAY_SET_H