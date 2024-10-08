# fmt::display - A Flexible C++ Formatting and Testing Library

`fmt::display` is a header-only C++ library that provides a flexible and extensible way to format and display various data types. Additionally, the library now includes a simple testing framework (`test::assert.h`) that allows for easy creation and execution of unit tests within your C++ project.

## Features

- **Custom display implementations** for user-defined types.
- **ANSI color support** for terminal output.
- **Built-in support for standard containers** like `vector`, `map`, and `set`.
- **Support for C++17 features** like `std::optional` and `std::variant`.
- **Simple testing framework** for creating and running unit tests.
- **Compile-time type checking** for printable types.
- **String-building capabilities** with the `fmtout` class.
- **Variadic template functions** for flexible printing.

## Requirements

- C++11 compatible compiler.
- Header-only library (no compilation needed).

## Installation

1. Clone this repository or download the `fmt.display.h` and `test.assert.h` files.
2. Include the headers in your C++ project:

```cpp
#include "fmt.display.h"
#include "test.assert.h"
```

## Usage

### Basic Printing

```cpp
#include "fmt.display.h"

int main() {
    fmt::println("Hello, world!");
    fmt::print("Value: ", 42, "\n");
    return 0;
}
```

Output:
```
Hello, world!
Value: 42
```

### Custom Types

Define a `Display` specialization for your custom types:

```cpp
struct Point {
    int x, y;
};

template<>
struct fmt::Display<Point> {
    static std::string print(const Point& p) {
        return fmt::sprint("(", p.x, ", ", p.y, ")");
    }
};

int main() {
    Point p{10, 20};
    fmt::println("Point: ", p);
    return 0;
}
```

Output:
```
Point: (10, 20)
```

### Container Support

The library provides built-in support for standard containers:

```cpp
#include <vector>
#include <map>
#include <set>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::map<std::string, int> map = {{"one", 1}, {"two", 2}};
    std::set<char> set = {'a', 'b', 'c'};

    fmt::println("Vector: ", vec);
    fmt::println("Map: ", map);
    fmt::println("Set: ", set);

    return 0;
}
```

Output:
```
Vector: [1, 2, 3, 4, 5]
Map: {one: 1, two: 2}
Set: {a, b, c}
```

### ANSI Colors

Use ANSI color codes for terminal output:

```cpp
fmt::println(ansi::red, "Error: ", ansi::reset, "Something went wrong!");
```

Output (colors may not be visible here):
```
Error: Something went wrong!
```
(The word "Error:" would appear in red in a terminal that supports ANSI colors)

### String Building

Use the `fmtout` class for building complex strings:

```cpp
fmt::fmtout out;
out << "Hello, " << ansi::blue << "world" << ansi::reset << "!";
fmt::println(out);
```

Output (colors may not be visible here):
```
Hello, world!
```
(The word "world" would appear in blue in a terminal that supports ANSI colors)

### Advanced Usage

The library also supports C++17 features like `std::optional` and `std::variant`:

```cpp
#include <optional>
#include <variant>

int main() {
    std::optional<int> opt1 = 42;
    std::optional<int> opt2;
    fmt::println("Optional with value: ", opt1);
    fmt::println("Optional without value: ", opt2);

    std::variant<int, float, std::string> var1 = 10;
    std::variant<int, float, std::string> var2 = 3.14f;
    std::variant<int, float, std::string> var3 = "Hello";
    fmt::println("Variant with int: ", var1);
    fmt::println("Variant with float: ", var2);
    fmt::println("Variant with string: ", var3);

    return 0;
}
```

Output:
```
Optional with value: Some(42)
Optional without value: None
Variant with int: Variant(10)
Variant with float: Variant(3.14)
Variant with string: Variant(Hello)
```

### Testing Framework

The `test::assert.h` file adds a simple and intuitive way to write unit tests for your C++ code. It includes assertion functions and a testing runner.

#### Writing Tests

```cpp
#include "test.assert.h"

int main() {
    RUN_TESTS;
    return 0;
}

MAKE_TESTS{
    It(divide by zero){
        asserteq(1 / 1, 1);
    }
    It(simple equality test){
        asserteq("test", "test");
    }
    {
        assert(42 > 0);
    }
}
```

#### Output Example

```
test 1 passed...   [1 / 1:`1` == 1:`1`]      It(divide by zero)
test 2 passed...   ["test":`test` == "test":`test`]      It(simple equality test)
test 3 passed...   [42 > 0:`True` == True]      It(test case 3)
Result : 
        3 tests passed
        0 tests failed
```

This framework allows you to structure and run your tests efficiently with clear output indicating which tests passed or failed.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available under the [MIT License](LICENSE).

## Future Improvements

We're always looking to improve `fmt::display` and the testing framework. Here are some areas we're considering for future development:

1. Performance optimizations.
2. Support for more complex formatting options (padding, alignment, etc.).
3. Integration with existing logging libraries.
4. More extensive testing suite.
5. Additional specializations for other standard library types.
6. Expanded functionality for the testing framework.

If you have any suggestions or would like to contribute to these efforts, please open an issue or submit a pull request!
