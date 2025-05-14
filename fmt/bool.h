// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

#include "display.h"
#ifndef FMT_DISPLAY_BOOL_H
#define FMT_DISPLAY_BOOL_H
template<>
struct fmt::Display<bool> {
    static std::string print(const bool &data) {
        if (data) return "True";
        else return "False";
    }
};
#endif // FMT_DISPLAY_BOOL_H