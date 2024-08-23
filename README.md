# fmt-display-cpp
A lightweight C++ library for custom formatted output using templates, featuring type-based printing and support for standard and custom types.

## Features

- **Custom Formatting**: Define custom print formats for your types by specializing the `fmt::Display` template.
- **Vector Support**: Automatically handle nested `std::vector` types.
- **Stream-Based Output**: Use `fmt::fmtout` to collect formatted output as a string.
- **Flexibility**: Print and format standard types and user-defined types seamlessly.

## Getting Started

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/fmt-display.git
   ```

2. **Include the Header**

   Include the `fmt.display.h` header in your project:

   ```cpp
   #include "fmt.display.h"
   ```

### Usage

#### Custom Display for User-Defined Types

To customize the output for your own types, specialize the `fmt::Display` template. For example:

```cpp
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

template<>
struct fmt::Display<Point> {
    static std::string print(const Point &data) {
        return fmt::sprint('(', data.x, ',', data.y, ')');
    }
};
```

#### Printing Vectors

The library provides support for nested `std::vector` types. For example:

```cpp
std::vector<float> f = {1.0, 2.2, 3.0};
fmt::println(f); // Output: [1.0, 2.2, 3.0]

std::vector<std::vector<float>> p = {f, f, f};
fmt::println(p); // Output: [[1.0, 2.2, 3.0], [1.0, 2.2, 3.0], [1.0, 2.2, 3.0]]
```

#### Using `fmt::fmtout` for Collecting Output

You can use `fmt::fmtout` to collect output as a string:

```cpp
fmt::fmtout result;
result.println(f, '\n', p);
result.println(pp);
std::cout << result.str() << std::endl;
```

#### Printing Custom Types

Define how custom types should be printed by specializing the `fmt::Display` template. For example:

```cpp
class Complex {
public:
    float r, i;
    Complex(float r, float i) : r(r), i(i) {}
};

template<>
struct fmt::Display<Complex> {
    static std::string print(const Complex &data) {
        fmt::fmtout result;
        result.print(data.r, '+');
        result.print(data.i, 'i');
        return result.str();
    }
};
```

#### Example Usage

```cpp
int main() {
    std::vector<float> f = {1.0, 2.2, 3.0};
    std::vector<std::vector<float>> p = {f, f, f};
    std::vector<std::vector<std::vector<float>>> pp = {p, p, p};
    
    fmt::println(f);
    fmt::println(p);
    fmt::println(pp);
    
    fmt::fmtout result;
    result.println(f, '\n', p);
    result.println(pp);
    std::cout << result.str() << std::endl;
    
    Point point(0, 0);
    fmt::println("point : ", point);
    
    Complex c(3.8, 1.2);
    fmt::print("Complex : ", c);
}
```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request to suggest improvements or report bugs.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
