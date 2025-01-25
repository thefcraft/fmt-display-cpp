#include "display.h"

// Convenience function to print arrays
namespace fmt{
    template<typename T>
    std::string sprint_array(const T* arr, size_t size) {
        fmt::fmtout result;
        result.print('[');
        bool first = true;
        for (size_t i = 0; i < size; i++) {
            if (!first) result.print(", ");
            result.print(arr[i]);
            first = false;
        }
        result.print(']');
        return result.str();
    }
}
