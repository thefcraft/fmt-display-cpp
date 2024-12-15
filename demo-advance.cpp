#include "fmt/full.h"
#include <vector>
#include <map>
#include <optional>
#include <variant>

// Example custom type
struct Point {
    int x, y;
};

// Implement Display for Point
template<>
struct fmt::Display<Point> {
    static std::string print(const Point& p) {
        return fmt::format_string("Point(%d, %d)", p.x, p.y);
    }
};

// Example class with multiple fields
class User {
    std::string name;
    int age;
public:
    User(std::string n, int a) : name(n), age(a) {}
    
    friend struct fmt::Display<User>;
};

// Implement Display for User
template<>
struct fmt::Display<User> {
    static std::string print(const User& user) {
        fmt::fmtout out;
        out << ansi::cyan << "User" << ansi::reset << "{\n\tname: " << ansi::green << user.name << ansi::reset 
            << ",\n\tage: " << ansi::yellow << user.age << ansi::reset << "\n}";
        return out.str();
    }
};

int main() {
    // Basic printing with colors
    fmt::println(ansi::blue, "=== Basic Printing Demo ===", ansi::reset);
    fmt::println("Hello, ", ansi::green, "World", ansi::reset, "!");
    fmt::println();

    // Container printing
    fmt::println(ansi::blue, "=== Container Demo ===", ansi::reset);
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::map<std::string, int> scores = {{"Alice", 100}, {"Bob", 85}};
    std::set<std::string> names = {"John", "Jane", "Alice"};
    
    fmt::println("Vector: ", numbers);
    fmt::println("Map: ", scores);
    fmt::println("Set: ", names);
    fmt::println();

    // Modern C++ types
    fmt::println(ansi::blue, "=== Modern C++ Types Demo ===", ansi::reset);
    std::optional<int> opt_value = std::make_optional(42);
    std::optional<int> opt_empty;
    std::variant<int, std::string> var_int = 123;
    std::variant<int, std::string> var_str = "hello";

    fmt::println("Optional (Some): ", opt_value);
    fmt::println("Optional (None): ", opt_empty);
    fmt::println("Variant (int): ", var_int);
    fmt::println("Variant (string): ", var_str);
    fmt::println();

    // Custom types
    fmt::println(ansi::blue, "=== Custom Types Demo ===", ansi::reset);
    Point p{10, 20};
    User user{"Alice", 25};
    
    fmt::println("Point: ", p);
    fmt::println("User: ", user);
    fmt::println();

    // fmtout usage
    fmt::println(ansi::blue, "=== fmtout Demo ===", ansi::reset);
    fmt::fmtout out;
    out << "Complex " << ansi::red << "formatted" << ansi::reset 
        << " output with " << numbers << " and " << user;
    fmt::println(out);

    // String formatting
    fmt::println(ansi::blue, "=== String Formatting Demo ===", ansi::reset);
    std::string formatted = fmt::format_string("Pi is approximately %.2f", 3.14159);
    fmt::println(formatted);

    // ANSI styles showcase
    fmt::println(ansi::blue, "\n=== ANSI Styles Demo ===", ansi::reset);
    fmt::println(ansi::bold, "Bold text");
    fmt::println(ansi::italic, "Italic text");
    fmt::println(ansi::underline, "Underlined text");
    fmt::println(ansi::blink, "Blinking text");
    fmt::println(ansi::reverse, "Reversed text");
    fmt::println(ansi::strikethrough, "Strikethrough text", ansi::reset);

    return 0;
}