import Link from 'next/link'
import { Button } from "@/components/ui/button"
import { CodeBlock } from '@/components/CodeBlock'
import { Card, CardHeader, CardTitle, CardDescription, CardContent } from "@/components/ui/card"
import { ArrowRight, Book, Code, Lightbulb, Users } from 'lucide-react'
import { AppSidebar } from '@/components/app-sidebar'
import { SidebarInset } from '@/components/ui/sidebar'
import { Header } from '@/components/header'

export default function DocsPage() {
  const quickStartCode = `
#include "fmt/display.h"
#include "fmt/vector.h"
#include <vector>

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  fmt::println("Numbers: ", numbers); // [1, 2, 3, 4, 5]
  fmt::println(ansi::green, "Hello, ", ansi::red, "World!", ansi::reset);
  return 0;
}
`.trim()

  return (<>
    <AppSidebar />
    <SidebarInset className="overflow-auto">
    <Header />
    <div className="max-w-5xl mx-auto px-4 py-12 w-full">
      <div className="text-center mb-12 w-full overflow-auto">
        <h1 className="text-2xl sm:text-5xl font-extrabold mb-4 bg-gradient-to-r from-blue-600 to-purple-600 bg-clip-text text-transparent">
          <Link href="/">
            fmt-display-cpp Documentation
          </Link>
        </h1>
        <p className="text-xs sm:text-xl text-muted-foreground mb-8 max-w-2xl mx-auto">
          A modern C++ library for effortless formatting and display of objects and containers.
        </p>
        <div className="flex justify-center max-w-sm mx-auto flex-col sm:flex-row gap-4">
          <Button asChild size="lg">
            <Link href="/docs/getting-started">
              Get Started <ArrowRight className="ml-2 h-4 w-4" />
            </Link>
          </Button>
          <Button asChild variant="outline" size="lg">
            <Link href="/docs/api-reference">API Reference</Link>
          </Button>
        </div>
      </div>

      <section className="mb-16">
        <h2 className="text-3xl font-bold mb-6 text-center">Key Features</h2>
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          {[
            {
              title: "Easy-to-use API",
              description: "Customize object display with a simple and intuitive API",
              icon: <Code className="h-8 w-8 text-blue-500" />,
            },
            {
              title: "ANSI Styling",
              description: "Add colors and text formatting to your console output",
              icon: <Lightbulb className="h-8 w-8 text-yellow-500" />,
            },
            {
              title: "Type-safe Formatting",
              description: "Catch formatting errors at compile-time",
              icon: <Book className="h-8 w-8 text-green-500" />,
            },
          ].map((feature, index) => (
            <Card key={index} className="flex flex-col items-center text-center p-6">
              <div className="mb-4">{feature.icon}</div>
              <CardTitle className="mb-2">{feature.title}</CardTitle>
              <CardDescription>{feature.description}</CardDescription>
            </Card>
          ))}
        </div>
      </section>

      <section className="mb-16">
        <h2 className="text-3xl font-bold mb-6">Quick Start</h2>
        <Card>
          <CardHeader>
            <CardTitle>Get started with fmt-display-cpp in just a few lines of code:</CardTitle>
          </CardHeader>
          <CardContent>
            <CodeBlock
              title="main.cpp"
              language="cpp"
              code={quickStartCode}
            />
          </CardContent>
        </Card>
      </section>

      <section className="mb-16">
        <h2 className="text-3xl font-bold mb-6 text-center">Explore Documentation</h2>
        <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-6">
          {[
            { title: "Core Features", href: "/docs/core-features", description: "Learn about the main capabilities of fmt-display-cpp" },
            { title: "Advanced Topics", href: "/docs/advanced-topics", description: "Dive deeper into complex usage scenarios" },
            { title: "Examples", href: "/docs/examples", description: "See practical code samples and use cases" },
            { title: "API Reference", href: "/docs/api-reference", description: "Detailed documentation of all components" },
            { title: "Community & Contributing", href: "/docs/community", description: "Join the community and contribute to the project" },
          ].map((item, index) => (
            <Card key={index} className="flex flex-col">
              <CardHeader>
                <CardTitle className="text-lg">{item.title}</CardTitle>
                <CardDescription>{item.description}</CardDescription>
              </CardHeader>
              <CardContent className="flex-grow flex items-end">
                <Button asChild variant="ghost" className="w-full mt-4">
                  <Link href={item.href}>
                    Explore <ArrowRight className="ml-2 h-4 w-4" />
                  </Link>
                </Button>
              </CardContent>
            </Card>
          ))}
        </div>
      </section>

      <section>
        <h2 className="text-3xl font-bold mb-6 text-center">Join Our Community</h2>
        <Card>
          <CardContent className="flex flex-col sm:flex-row items-center justify-between p-6">
            <div className="flex items-center mb-4 sm:mb-0">
              <Users className="h-12 w-12 text-purple-500 mr-4" />
              <div>
                <h3 className="text-xl font-semibold mb-1">Get Involved</h3>
                <p className="text-muted-foreground">
                  Join our community to get help, share your projects, and contribute.
                </p>
              </div>
            </div>
            <div className="flex gap-4">
              <Button asChild variant="outline">
                <a href="https://github.com/thefcraft/fmt-display-cpp" target="_blank" rel="noopener noreferrer">GitHub</a>
              </Button>
              {/* <Button asChild variant="outline"> */}
              <Button variant="outline" disabled>
                {/* <a href="https://discord.gg/xxxxx" target="_blank" rel="noopener noreferrer">Discord</a> */}
                Discord
              </Button>
            </div>
          </CardContent>
        </Card>
      </section>
    </div>
  </SidebarInset></>)
}

