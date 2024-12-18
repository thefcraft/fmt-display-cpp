import { CodeBlock,InlineCode } from '@/components/CodeBlock' 
import { Header } from '@/components/header'
import { AppSidebar } from '@/components/app-sidebar'
import { SidebarInset } from '@/components/ui/sidebar'
export default function ApiReferencePage() {
  const displayTraitCode = `
template<typename T>
struct fmt::Display {
    static std::string print(const T& value);
};

// Example specialization
template<>
struct fmt::Display<MyCustomType> {
    static std::string print(const MyCustomType& value) {
        // Custom implementation
        return fmt::format_string("MyCustomType(%s)", value.toString());
    }
};
  `.trim()

  const fmtoutMethodsCode = `
class fmt::fmtout {
public:
    // Append a value to the internal buffer
    template<typename T>
    fmtout& operator<<(const T& value);

    // Get the formatted string
    std::string str() const;

    // Clear the internal buffer
    void clear();
};
  `.trim()

  const printFormatterMethodsCode = `
class fmt::PrintFormatter {
public:
    // Constructor
    PrintFormatter(const std::string& sep = "", const std::string& end = "");

    // Print multiple arguments
    template<typename... Args>
    void print(const Args&... args);

    // Return formatted string without printing
    template<typename... Args>
    std::string sprint(const Args&... args);
};
  `.trim()

  const helperFunctionsCode = `
namespace fmt {
    // Format a string with type-safe arguments
    template<typename... Args>
    std::string format_string(const std::string& format, Args... args);

    // Print without newline
    template<typename... Args>
    void print(const Args&... args);

    // Print with newline
    template<typename... Args>
    void println(const Args&... args);
}
  `.trim()

  return (<>
    <AppSidebar currIndex={5} />
    <SidebarInset className="overflow-auto">
    <Header page='api-reference' />
    <div className="max-w-4xl mx-auto px-4 py-8 w-full">
      <h1 className="text-4xl font-bold mb-6">API Reference for fmt-display-cpp</h1>
      <p className="text-xl text-muted-foreground mb-8">
        Comprehensive documentation of fmt-display-cpp's core components and functions.
      </p>
      
      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='display-trait'>Display Trait</h2>
        <p className="mb-4">
          The <InlineCode>fmt::Display</InlineCode> trait is the core of fmt-display-cpp's customization capabilities:
        </p>
        <CodeBlock
          title="fmt::Display"
          language="cpp"
          code={displayTraitCode}
        />
        <p className="mt-4">
          Specialize this trait for your custom types to control how they are displayed in all fmt-display-cpp operations.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='fmtout-methods'>fmtout Methods</h2>
        <p className="mb-4">
          The <InlineCode>fmt::fmtout</InlineCode> class provides a stream-like interface for building formatted strings:
        </p>
        <CodeBlock
          title="fmt::fmtout"
          language="cpp"
          code={fmtoutMethodsCode}
        />
        <p className="mt-4">
          Use <InlineCode>fmtout</InlineCode> when you need to build complex formatted strings with multiple components or styling changes.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='printformatter-methods'>PrintFormatter Methods</h2>
        <p className="mb-4">
          The <InlineCode>fmt::PrintFormatter</InlineCode> class allows for customized printing with user-defined separators and end-of-line characters:
        </p>
        <CodeBlock
          title="fmt::PrintFormatter"
          language="cpp"
          code={printFormatterMethodsCode}
        />
        <p className="mt-4">
          Use <InlineCode>PrintFormatter</InlineCode> to create specialized formatting for various output needs, such as CSV generation or simple serialization.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='ansi-namespace-constants'>ANSI Namespace Constants</h2>
        <p className="mb-4">
          The <InlineCode>ansi</InlineCode> namespace provides constants for text styling:
        </p>
        <ul className="list-disc pl-6 space-y-2">
          <li><InlineCode>ansi::reset</InlineCode>: Reset all styling</li>
          <li><InlineCode>ansi::bold</InlineCode>: Bold text</li>
          <li><InlineCode>ansi::italic</InlineCode>: Italic text</li>
          <li><InlineCode>ansi::underline</InlineCode>: Underlined text</li>
          <li><InlineCode>ansi::red</InlineCode>: Red text</li>
          <li><InlineCode>ansi::green</InlineCode>: Green text</li>
          <li><InlineCode>ansi::blue</InlineCode>: Blue text</li>
          <li><InlineCode>ansi::yellow</InlineCode>: Yellow text</li>
          <li><InlineCode>ansi::magenta</InlineCode>: Magenta text</li>
          <li><InlineCode>ansi::cyan</InlineCode>: Cyan text</li>
        </ul>
      </section>

      <section>
        <h2 className="text-2xl font-semibold mb-4" id='helper-functions'>Helper Functions</h2>
        <p className="mb-4">
          fmt-display-cpp provides several helper functions for common formatting tasks:
        </p>
        <CodeBlock
          title="Helper Functions"
          language="cpp"
          code={helperFunctionsCode}
        />
        <p className="mt-4">
          These functions provide convenient ways to format strings and print output with or without newlines.
        </p>
      </section>
    </div>
    </SidebarInset></>)
}

