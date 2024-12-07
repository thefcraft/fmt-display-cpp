#include "display.h"
#include <variant>
template<typename... Types>
struct fmt::Display<std::variant<Types...>> {
    static std::string print(const std::variant<Types...>& var) {
        return std::visit([](const auto& value) {
            return sprint("Variant(", value, ")");
        }, var);
    }
};