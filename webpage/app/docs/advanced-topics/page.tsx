import { CodeBlock, InlineCode } from '@/components/CodeBlock'
import { Header } from '@/components/header'
import { AppSidebar } from "@/components/app-sidebar"
import {
  SidebarInset
} from "@/components/ui/sidebar"
export default function AdvancedTopicsPage() {
  const customTypeSpecializationCode = `
#include "fmt/display.h"
#include "fmt/vector.h"
#include <vector>

// A more complex custom type
struct Person {
    std::string name;
    int age;
    std::vector<std::string> hobbies;
};

// Specialization for Person
template<>
struct fmt::Display<Person> {
    static std::string print(const Person& p) {
        fmt::fmtout out;
        out << "Person(" << ansi::bold << p.name << ansi::reset
            << ", age: " << p.age << ", hobbies: " << p.hobbies << ")";
        return out.str();
    }
};

int main() {
    Person alice{"Alice", 30, {"reading", "hiking", "photography"}};
    fmt::println(alice);
    
    std::vector<Person> people = {
        {"Bob", 25, {"gaming", "cooking"}},
        {"Charlie", 35, {"traveling", "music"}}
    };
    fmt::println("People: ", people);

    return 0;
}
  `.trim()

  const errorHandlingCode = `
#include "fmt/display.h"
#include <stdexcept>

// Custom error type
struct FormatError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

template<>
struct fmt::Display<FormatError> {
    static std::string print(const FormatError& e) {
        return fmt::format_string("FormatError: %s", e.what());
    }
};

void format_with_error() {
    try {
        throw FormatError("Invalid format string");
    } catch (const FormatError& e) {
        fmt::println(ansi::red, e, ansi::reset);
    }
}

int main() {
    format_with_error();
    return 0;
}
  `.trim()

  const compileTimeTypeChecksCode = `
#include "fmt/display.h"
#include <type_traits>

// Example usage
struct Printable {};
template<>
struct fmt::Display<Printable> {
    static std::string print(const Printable&) { return "Printable"; }
};

struct NonPrintable {};

int main() {
    // fmt::detail::ShouldPrint<T>  for checking struct fmt::Display<T>
    // fmt::detail::is_printable<T> for checking std::cout<<(<T>)
    static_assert(fmt::detail::is_printable<int>::value, "int should be printable");
    static_assert(fmt::detail::ShouldPrint<Printable>::value, "Printable should be printable");
    static_assert(!fmt::detail::ShouldPrint<NonPrintable>::value, "NonPrintable should not be printable");

    return 0;
}
  `.trim()

  const extendingFmtDisplayCode = `
#include "fmt/display.h"
#include <optional>

// Extending fmt::display to work with std::optional
template<typename T>
struct fmt::Display<std::optional<T>> {
    static std::string print(const std::optional<T>& opt) {
        if (opt) {
            return fmt::print.sprint("Some(", *opt, ")");
        } else {
            return "None";
        }
    }
};

int main() {
    std::optional<int> some_value = 42;
    std::optional<int> no_value;

    fmt::println("Some value: ", some_value);
    fmt::println("No value: ", no_value);

    return 0;
}
  `.trim()

  return (<>
    <AppSidebar currIndex={4} />
    <SidebarInset className="overflow-auto">
    <Header page='advanced-topics'/>
    <div className="max-w-4xl mx-auto px-4 py-8 w-full">
      <h1 className="text-4xl font-bold mb-6">Advanced Topics in fmt-display-cpp</h1>
      <p className="text-xl text-muted-foreground mb-8">
        Explore advanced features and techniques to get the most out of fmt-display-cpp.
      </p>
      
      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='custom-type-specialization'>Custom Type Specialization</h2>
        <p className="mb-4">
          Learn how to create detailed specializations for complex custom types:
        </p>
        <CodeBlock
          title="custom_type_specialization.cpp"
          language="cpp"
          code={customTypeSpecializationCode}
        />
        <p className="mt-4">
          This example demonstrates how to create a custom <InlineCode>fmt::Display</InlineCode> specialization for a more complex type, 
          including nested containers and ANSI styling.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='error-handling'>Error Handling</h2>
        <p className="mb-4">
          Implement custom error handling and formatting for your application:
        </p>
        <CodeBlock
          title="error_handling.cpp"
          language="cpp"
          code={errorHandlingCode}
        />
        <p className="mt-4">
          This example shows how to create and handle custom error types with fmt-display-cpp, 
          including specialized formatting for error messages.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='compile-time-type-checks'>Compile-Time Type Checks</h2>
        <p className="mb-4">
          Implement compile-time checks to ensure type safety:
        </p>
        <CodeBlock
          title="compile_time_checks.cpp"
          language="cpp"
          code={compileTimeTypeChecksCode}
        />
        <p className="mt-4">
          This example demonstrates how to create type traits for compile-time checks, 
          ensuring that only printable types are used with fmt-display-cpp.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='extending-fmt-display'>Extending fmt::display</h2>
        <p className="mb-4">
          Learn how to extend fmt-display-cpp to work with third-party libraries and types:
        </p>
        <CodeBlock
          title="extending_fmt_display.cpp"
          language="cpp"
          code={extendingFmtDisplayCode}
        />
        <p className="mt-4">
          This example shows how to extend fmt-display-cpp to work with <InlineCode>std::optional</InlineCode>, 
          demonstrating how you can integrate the library with other C++ features and libraries.
        </p>
      </section>

      <section>
        <h2 className="text-2xl font-semibold mb-4">Best Practices</h2>
        <ul className="list-disc pl-6 space-y-2">
          <li>Always provide a <InlineCode>fmt::Display</InlineCode> specialization for your custom types to ensure consistent formatting.</li>
          <li>Use ANSI styling judiciously to enhance readability without overwhelming the user.</li>
          <li>Implement compile-time checks where possible to catch formatting errors early.</li>
          <li>When extending fmt-display-cpp, consider performance implications, especially for frequently used types.</li>
          <li>Document your custom formatters and extensions to make it easier for other developers to use and maintain your code.</li>
        </ul>
      </section>
    </div>
    </SidebarInset>
    </>)
}

