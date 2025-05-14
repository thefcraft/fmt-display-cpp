// Copyright (c) 2025, ThefCraft
// License: This project is licensed under the MIT License.

#include "display.h"
#include <variant>
#ifndef FMT_DISPLAY_VARIANT_H
#define FMT_DISPLAY_VARIANT_H
template<typename... Types>
struct fmt::Display<std::variant<Types...>> {
    static std::string print(const std::variant<Types...>& var) {
        return std::visit([](const auto& value) {
            return fmt::print.sprint("Variant(", value, ")");
        }, var);
    }
};
#endif // FMT_DISPLAY_VARIANT_H