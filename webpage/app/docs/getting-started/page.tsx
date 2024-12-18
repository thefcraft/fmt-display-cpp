import { CodeBlock, InlineCode } from '@/components/CodeBlock'
import { Tabs, TabsContent, TabsList, TabsTrigger } from "@/components/ui/tabs"
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card"
import { Header } from '@/components/header'
import { AppSidebar } from "@/components/app-sidebar"
import {
  SidebarInset
} from "@/components/ui/sidebar"

export default function GettingStartedPage() {
  const installationCode = `
git clone https://github.com/thefcraft/fmt-display-cpp.git
cd fmt-display-cpp
cp -r fmt {your-project-path}
  `.trim()

  const cmakeCode = `
# first git clone https://github.com/thefcraft/fmt-display-cpp.git
# Add the fmt library directory
include_directories(path/to/fmt-display-cpp/fmt)
  `.trim()

  const quickStartCode = `
#include "fmt/full.h"
#include <vector>
#include <map>
// Custom type output
struct Point { int x, y; };

template<>
struct fmt::Display<Point> {
    static std::string print(const Point& p) {
        return fmt::format_string("(%d, %d)", p.x, p.y);
    }
};

int main() {
    // Basic output
    fmt::println("Hello, World!");

    // Styled output
    fmt::println(ansi::green, "Success:", ansi::reset, " Operation completed.");

    // Container output
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    fmt::println("Numbers: ", numbers);


    Point p{10, 20};
    fmt::println("Point: ", p);

    // Complex data structures
    std::map<std::string, Point> locations = {
        {"Home", {0, 0}},
        {"Work", {10, 5}},
        {"Park", {-5, 15}}
    };
    fmt::println("Locations: ", locations);

    return 0;
}
  `.trim()

  return (<>
    <AppSidebar currIndex={2} />
    <SidebarInset className="overflow-auto">
    <Header page='getting-started' />
    <div className="max-w-4xl mx-auto px-4 py-8 w-full">
      <h1 className="text-4xl font-bold mb-6">Getting Started with fmt-display-cpp</h1>
      <p className="text-xl text-muted-foreground mb-8">
        Learn how to install, set up, and start using fmt-display-cpp in your projects.
      </p>
      
      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='installation'>Installation</h2>
        <p className="mb-4">
          To get started with fmt-display-cpp, follow these steps to install the library:
        </p>
        <Tabs defaultValue="cmake" className="w-full mb-6">
          <TabsList>
            <TabsTrigger value="cmake">CMake</TabsTrigger>
            <TabsTrigger value="manual">Manual Installation</TabsTrigger>
          </TabsList>
          <TabsContent value="cmake">
            <CodeBlock
              title="CMakeLists.txt"
              language="cmake"
              code={cmakeCode}
            />
          </TabsContent>
          <TabsContent value="manual">
            <CodeBlock
              title="Terminal"
              language="bash"
              code={installationCode}
            />
          </TabsContent>
        </Tabs>
        <p className="mt-4">
          After installation, include the library in your project:
        </p>
        <CodeBlock
          language="cpp"
          code='#include "fmt/display.h"'
        />
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='quick-start-guide'>Quick Start Guide</h2>
        <p className="mb-4">
          Here's a comprehensive example to get you started with fmt-display-cpp:
        </p>
        <CodeBlock
          title="quick_start.cpp"
          language="cpp"
          code={quickStartCode}
        />
        <p className="mt-4">
          This example demonstrates basic output, styled output, container output, custom type output, and handling complex data structures.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id='key-concepts'>Key Concepts</h2>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
          <Card>
            <CardHeader>
              <CardTitle>fmt::Display Trait</CardTitle>
              <CardDescription>Customize how your types are displayed</CardDescription>
            </CardHeader>
            <CardContent>
              <p>
                Specialize <InlineCode>fmt::Display&lt;T&gt;</InlineCode> for your custom types to control their formatting.
              </p>
            </CardContent>
          </Card>
          <Card>
            <CardHeader>
              <CardTitle>ANSI Styling</CardTitle>
              <CardDescription>Add colors and formatting to your output</CardDescription>
            </CardHeader>
            <CardContent>
              <p>
                Use <InlineCode>ansi::*</InlineCode> constants to add colors and styles to your text.
              </p>
            </CardContent>
          </Card>
          <Card>
            <CardHeader>
              <CardTitle>Container Support</CardTitle>
              <CardDescription>Easily print standard containers</CardDescription>
            </CardHeader>
            <CardContent>
              <p>
                fmt-display-cpp provides built-in support for printing standard containers like vectors, maps, and sets.
              </p>
            </CardContent>
          </Card>
          <Card>
            <CardHeader>
              <CardTitle>Safe Formatting</CardTitle>
              <CardDescription>Type-safe string formatting</CardDescription>
            </CardHeader>
            <CardContent>
              <p>
                Use <InlineCode>fmt::format_string</InlineCode> for type-safe string formatting.
              </p>
            </CardContent>
          </Card>
        </div>
      </section>

      <section>
        <h2 className="text-2xl font-semibold mb-4">Next Steps</h2>
        <p className="mb-4">
          Now that you've got the basics, explore these topics to learn more:
        </p>
        <ul className="list-disc pl-6 space-y-2">
          <li>Learn about <a href="/docs/core-features" className="text-blue-500 hover:underline">Core Features</a> in depth</li>
          <li>Explore <a href="/docs/advanced-topics" className="text-blue-500 hover:underline">Advanced Topics</a> for more complex usage</li>
          <li>Check out the <a href="/docs/examples" className="text-blue-500 hover:underline">Examples</a> for practical use cases</li>
          <li>Refer to the <a href="/docs/api-reference" className="text-blue-500 hover:underline">API Reference</a> for detailed documentation</li>
        </ul>
      </section>
    </div>
  </SidebarInset></>)
}

