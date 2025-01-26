#include "display.h"

// Template for pointer
template<typename T>
struct fmt::Display<T*> {
    static std::string print(const T* data) {
        fmt::fmtout result;
        // result.print("ptr(\n");
        result.print("ptr(", *data, ')');
        // result.print("\n 0x", reinterpret_cast<std::uintptr_t>(static_cast<const void*>(data)), ')');
        return result.str();
    }
};
template<>
struct fmt::Display<const char*> {
    static std::string print(const char* data) {
        fmt::fmtout result;
        std::string _data = data;
        result.print(_data);
        return result.str();
    }
};