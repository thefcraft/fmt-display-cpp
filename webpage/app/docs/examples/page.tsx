import { AppSidebar } from '@/components/app-sidebar'
import { CodeBlock, InlineCode } from '@/components/CodeBlock'
import { Header } from '@/components/header'
import { SidebarInset } from '@/components/ui/sidebar'

export default function ExamplesPage() {
  const simpleOutputCode = `
#include "fmt/display.h"
#include "fmt/vector.h"
#include "fmt/map.h"
#include <vector>
#include <map>

int main() {
    // Basic output
    fmt::println("Hello, World!");

    // Styled output
    fmt::println(ansi::green, "Success:", ansi::reset, " Operation completed.");

    // Container output
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    fmt::println("Numbers: ", numbers);

    // Complex data structure
    std::map<std::string, std::vector<int>> data = {
        {"Alice", {90, 85, 92}},
        {"Bob", {78, 88, 76}},
        {"Charlie", {95, 91, 89}}
    };
    fmt::println("Student Scores: ", data);

    return 0;
}
  `.trim()

  const customTypeCode = `
#include "fmt/display.h"
#include "fmt/vector.h"
#include <vector>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

template<>
struct fmt::Display<Point> {
    static std::string print(const Point& p) {
        return fmt::format_string("(%d, %d)", p.x, p.y);
    }
};

int main() {
    Point p1(10, 20);
    Point p2(-5, 15);

    fmt::println("Point 1: ", p1);
    fmt::println("Point 2: ", p2);

    std::vector<Point> points = {p1, p2, Point(0, 0)};
    fmt::println("All points: ", points);

    return 0;
}
  `.trim()

  const styledOutputCode = `
#include "fmt/display.h"

int main() {
    fmt::println(ansi::bold, "Bold Text");
    fmt::println(ansi::red, "Red Text");
    fmt::println(ansi::green, "Green Text");
    fmt::println(ansi::blue, "Blue Text");

    fmt::fmtout out;
    out << "This is " << ansi::bold << "bold" << ansi::reset
        << " and this is " << ansi::red << "red" << ansi::reset
        << " and this is " << ansi::blue << ansi::italic << "blue italic" << ansi::reset;
    fmt::println(out);

    return 0;
}
  `.trim()

  const errorHandlingCode = `
#include "fmt/display.h"
#include <stdexcept>

class CustomError : public std::runtime_error {
public:
    CustomError(const std::string& message) : std::runtime_error(message) {}
};

template<>
struct fmt::Display<CustomError> {
    static std::string print(const CustomError& e) {
        return fmt::print.sprint(ansi::red, "CustomError: ", e.what(), ansi::reset);
    }
};

void may_throw() {
    throw CustomError("Something went wrong");
}

int main() {
    try {
        may_throw();
    } catch (const CustomError& e) {
        fmt::println(ansi::green, "Error caught: ", ansi::reset, e);
    }

    return 0;
}
  `.trim()

  return (<>
    <AppSidebar currIndex={6} />
    <SidebarInset className="overflow-auto">
    <Header page='examples' />
    <div className="max-w-4xl mx-auto px-4 py-8 w-full">
      <h1 className="text-4xl font-bold mb-6">Examples of fmt-display-cpp Usage</h1>
      <p className="text-xl text-muted-foreground mb-8">
        Explore practical examples demonstrating various features of fmt-display-cpp.
      </p>
      
      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='simple-output-example'>Simple Output Example</h2>
        <p className="mb-4">
          This example demonstrates basic output, styled output, and container output:
        </p>
        <CodeBlock
          title="simple_output.cpp"
          language="cpp"
          code={simpleOutputCode}
        />
        <p className="mt-4">
          This example shows how to use <InlineCode>fmt::println</InlineCode> for various types of output, 
          including styled text and complex data structures.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='custom-type-example'>Custom Type Example</h2>
        <p className="mb-4">
          Learn how to create and use custom type specializations:
        </p>
        <CodeBlock
          title="custom_type.cpp"
          language="cpp"
          code={customTypeCode}
        />
        <p className="mt-4">
          This example demonstrates how to specialize <InlineCode>fmt::Display</InlineCode> for a custom type 
          and use it with both individual instances and containers.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='styled-output-example'>Styled Output Example</h2>
        <p className="mb-4">
          Explore the ANSI styling capabilities of fmt-display-cpp:
        </p>
        <CodeBlock
          title="styled_output.cpp"
          language="cpp"
          code={styledOutputCode}
        />
        <p className="mt-4">
          This example shows how to use ANSI styling constants and the <InlineCode>fmt::fmtout</InlineCode> class 
          to create rich, colorful console output.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='error-handling-example'>Error Handling Example</h2>
        <p className="mb-4">
          Implement custom error handling and formatting:
        </p>
        <CodeBlock
          title="error_handling.cpp"
          language="cpp"
          code={errorHandlingCode}
        />
        <p className="mt-4">
          This example demonstrates how to create a custom error type, specialize <InlineCode>fmt::Display</InlineCode> for it, 
          and use it in a try-catch block with styled error output.
        </p>
      </section>

      <section>
        <h2 className="text-2xl font-semibold mb-4">Further Examples</h2>
        <p className="mb-4">
          For more advanced usage and examples, check out these topics:
        </p>
        <ul className="list-disc pl-6 space-y-2">
          <li><a href="/docs/advanced-topics#custom-type-specialization" className="text-blue-500 hover:underline">Custom Type Specialization</a></li>
          <li><a href="/docs/advanced-topics#compile-time-type-checks" className="text-blue-500 hover:underline">Compile-Time Type Checks</a></li>
          <li><a href="/docs/advanced-topics#extending-fmt-display" className="text-blue-500 hover:underline">Extending fmt::display</a></li>
        </ul>
      </section>
    </div>
  </SidebarInset></>)
}

