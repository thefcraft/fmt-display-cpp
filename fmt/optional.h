#include "display.h"
#include <optional>
template<typename T>
struct fmt::Display<std::optional<T>> {
    static std::string print(const std::optional<T>& opt) {
        if (opt) return fmt::print.sprint("Some(", *opt, ")");
        else return "None";
    }
};