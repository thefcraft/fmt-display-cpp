// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

#include "display.h"
#include <optional>
#ifndef FMT_DISPLAY_OPTIONAL_H
#define FMT_DISPLAY_OPTIONAL_H
template<typename T>
struct fmt::Display<std::optional<T>> {
    static std::string print(const std::optional<T>& opt) {
        if (opt) return fmt::print.sprint("Some(", *opt, ")");
        else return "None";
    }
};
#endif // FMT_DISPLAY_OPTIONAL_H