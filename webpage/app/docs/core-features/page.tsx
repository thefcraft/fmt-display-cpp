import { AppSidebar } from '@/components/app-sidebar'
import { CodeBlock, InlineCode } from '@/components/CodeBlock'
import { Header } from '@/components/header'
import {
  SidebarInset
} from "@/components/ui/sidebar"


export default function CoreFeaturesPage() {
  const ansiStylingCode = `
#include "fmt/display.h"

int main() {
    fmt::println(ansi::red, "Error: ", ansi::reset, "Something went wrong.");
    fmt::println(ansi::green, "Success: ", ansi::bold, "Operation completed.", ansi::reset);
    fmt::println(ansi::blue, "Info: ", ansi::italic, "This is some information.", ansi::reset);
    return 0;
}
  `.trim()

  const customDisplayCode = `
#include "fmt/display.h"
#include "fmt/vector.h"

struct Point { 
    int x, y; 
    
    // Constructor for convenience
    Point(int x, int y) : x(x), y(y) {}
};

template<>
struct fmt::Display<Point> {
    static std::string print(const Point& p) {
        return fmt::format_string("(%d, %d)", p.x, p.y);
    }
};

int main() {
    Point p{10, 20};
    fmt::println("Point: ", p);  // Output: Point: (10, 20)
    
    std::vector<Point> points = {{1, 2}, {3, 4}, {5, 6}};
    fmt::println("Points: ", points);  // Output: Points: [(1, 2), (3, 4), (5, 6)]
    
    return 0;
}
  `.trim()

  const safeFormattingCode = `
#include "fmt/display.h"

int main() {
    std::string name = "Alice";
    int age = 30;
    float height = 1.75f;

    // Type-safe formatting
    std::string message = fmt::format_string("%s is %d years old and %.2f meters tall.", 
                                             name.c_str(), age, height);
    fmt::println(message);

    // TODO: This would cause a compile-time error:
    // fmt::format_string("%d", "not a number");

    return 0;
}
  `.trim()

  const fmtoutCode = `
#include "fmt/display.h"

int main() {
    fmt::fmtout out;
    out << "The answer is " << ansi::bold << 42 << ansi::reset << "!";
    fmt::println(out);  // Output: The answer is 42! (with 42 in bold)

    out.clear();
    out << ansi::red << "Error: " << ansi::reset << "File not found.";
    fmt::println(out);  // Output: Error: File not found. (with "Error:" in red)

    return 0;
}
  `.trim()

  const printFormatterCode = `
#include "fmt/display.h"

int main() {
    fmt::PrintFormatter custom_println(", ", "\\n");
    custom_println(1, 2, 3);  // Output: 1, 2, 3\\n

    fmt::PrintFormatter custom_print(":", ";");
    custom_print("name", "Alice", "age", 30);  // Output: name:Alice:age:30;

    return 0;
}
  `.trim()

  return (<>
    <AppSidebar currIndex={3} />
    <SidebarInset className="overflow-auto"> 
    <Header page='core-features'/>
    <div className="max-w-4xl mx-auto px-4 py-8 w-full">
      <h1 className="text-4xl font-bold mb-6">Core Features of fmt-display-cpp</h1>
      <p className="text-xl text-muted-foreground mb-8">
        Explore the powerful features that make fmt-display-cpp a versatile and user-friendly formatting library.
      </p>
      
      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='ansi-styling'>ANSI Styling</h2>
        <p className="mb-4">
          fmt-display-cpp provides built-in support for ANSI styling, allowing you to add colors and text formatting to your console output easily.
        </p>
        <CodeBlock
          title="ansi_styling_example.cpp"
          language="cpp"
          code={ansiStylingCode}
        />
        <p className="mt-4">
          Available ANSI styles include colors (e.g., <InlineCode>ansi::red</InlineCode>, <InlineCode>ansi::green</InlineCode>), 
          text styles (e.g., <InlineCode>ansi::bold</InlineCode>, <InlineCode>ansi::italic</InlineCode>), 
          and <InlineCode>ansi::reset</InlineCode> to return to default styling.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='custom-display-trait'>Custom Display Trait</h2>
        <p className="mb-4">
          Customize how your types are displayed by specializing the <InlineCode>fmt::Display</InlineCode> trait. 
          This allows for seamless integration of custom types with fmt-display-cpp's formatting system.
        </p>
        <CodeBlock
          title="custom_display_example.cpp"
          language="cpp"
          code={customDisplayCode}
        />
        <p className="mt-4">
          By specializing <InlineCode>fmt::Display</InlineCode> for your custom types, you can control how they are 
          formatted in all fmt-display-cpp operations, including when they're part of containers.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='safe-string-formatting'>Safe String Formatting</h2>
        <p className="mb-4">
          fmt-display-cpp provides type-safe string formatting with <InlineCode>fmt::format_string</InlineCode>, 
          helping to catch formatting errors at compile-time.
        </p>
        <CodeBlock
          title="safe_formatting_example.cpp"
          language="cpp"
          code={safeFormattingCode}
        />
        <p className="mt-4">
          The <InlineCode>fmt::format_string</InlineCode> function ensures that the format string matches the 
          types of the provided arguments, preventing runtime formatting errors.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='fmtout-class'>fmtout Class</h2>
        <p className="mb-4">
          The <InlineCode>fmt::fmtout</InlineCode> class allows for complex formatting operations with a 
          stream-like interface, making it easy to build formatted strings.
        </p>
        <CodeBlock
          title="fmtout_example.cpp"
          language="cpp"
          code={fmtoutCode}
        />
        <p className="mt-4">
          <InlineCode>fmt::fmtout</InlineCode> is particularly useful when you need to build complex formatted 
          strings with multiple components or styling changes.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='printformatter-utility'>PrintFormatter Utility</h2>
        <p className="mb-4">
          The <InlineCode>fmt::PrintFormatter</InlineCode> utility allows for customized printing with 
          user-defined separators and end-of-line characters.
        </p>
        <CodeBlock
          title="print_formatter_example.cpp"
          language="cpp"
          code={printFormatterCode}
        />
        <p className="mt-4">
          <InlineCode>PrintFormatter</InlineCode> is highly customizable, allowing you to create specialized 
          formatting for various output needs, such as CSV generation or simple serialization.
        </p>
      </section>

      <section>
        <h2 className="text-2xl font-semibold mb-4" id='global-print-instances'>Global Print Instances</h2>
        <p className="mb-4">
          fmt-display-cpp provides global print instances for convenience:
        </p>
        <ul className="list-disc pl-6 space-y-2">
          <li><InlineCode>fmt::print</InlineCode>: Prints without a newline</li>
          <li><InlineCode>fmt::println</InlineCode>: Prints with a newline</li>
        </ul>
        <p className="mt-4">
          These global instances make it easy to quickly output formatted text without needing to create 
          custom <InlineCode>PrintFormatter</InlineCode> instances for common use cases.
        </p>
      </section>
    </div>
    </SidebarInset>
  </>)
}



