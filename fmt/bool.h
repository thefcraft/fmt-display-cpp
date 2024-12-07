#include "display.h"
template<>
struct fmt::Display<bool> {
    static std::string print(const bool &data) {
        if (data) return "True";
        else return "False";
    }
};