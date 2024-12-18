"use client"

import { Button } from "@/components/ui/button"
import { ArrowRight, Github, Code, Palette, Box, Zap, Shield, Terminal } from 'lucide-react'
import Link from "next/link"
import { motion } from "framer-motion"
import React from "react"
import { CodeBlock } from "@/components/CodeBlock"

export default function LandingPage() {
  return (
    <div className="flex flex-col min-h-screen bg-gradient-to-b from-gray-50 to-white dark:from-gray-900 dark:to-gray-800">
      <header className="px-4 lg:px-6 h-16 flex items-center w-full">
        <Link className="flex items-center justify-center" href="#">
          <Code className="h-6 w-6 mr-2 text-blue-600" />
          <span className="font-bold text-2xl bg-clip-text text-transparent bg-gradient-to-r from-blue-500 to-teal-400">fmt-display-cpp</span>
        </Link>
        <nav className="ml-auto flex gap-4 sm:gap-6">
          <Link className="hidden md:block text-sm font-medium hover:text-blue-600 transition-colors" href="#features">
            Features
          </Link>
          <Link className="hidden md:block text-sm font-medium hover:text-blue-600 transition-colors" href="#examples">
            Examples
          </Link>
          <Link className="hidden sm:block text-sm font-medium hover:text-blue-600 transition-colors" href="#installation">
            Installation
          </Link>
          <Link className="text-sm font-medium hover:text-blue-600 transition-colors" href="/docs">
            Docs
          </Link>
        </nav>
      </header>
      <main className="flex-1 w-full">
        <section className="w-full py-12 md:py-24 lg:py-32 xl:py-48">
          <div className="container px-4 md:px-6 mx-auto">
            <div className="flex flex-col items-center space-y-4 text-center">
              <motion.div
                initial={{ opacity: 0, y: 20 }}
                animate={{ opacity: 1, y: 0 }}
                transition={{ duration: 0.6 }}
                className="space-y-2"
              >
                <h1 className="text-3xl font-bold tracking-tighter sm:text-4xl md:text-5xl lg:text-6xl/none">
                  fmt-display-cpp
                </h1>
                <p className="mx-auto max-w-[700px] text-gray-500 md:text-xl dark:text-gray-400">
                  A Modern C++ Display Library for effortless formatting and output
                </p>
              </motion.div>
              <motion.div
                initial={{ opacity: 0, y: 20 }}
                animate={{ opacity: 1, y: 0 }}
                transition={{ duration: 0.6, delay: 0.2 }}
              >
                <Link href="/docs">
                  <Button className="mb-4 bg-blue-600 hover:bg-blue-700 text-white">
                    Get Started
                    <ArrowRight className="ml-2 h-4 w-4" />
                  </Button>
                </Link>
                <Link href="https://github.com/thefcraft/fmt-display-cpp">
                  <Button variant="outline" className="ml-4">
                    View on GitHub
                    <Github className="ml-2 h-4 w-4" />
                  </Button>
                </Link>
              </motion.div>
            </div>
          </div>
        </section>
        <section id="features" className="w-full py-12 md:py-24 lg:py-32 bg-gray-100 dark:bg-gray-800">
          <div className="container px-4 md:px-6 mx-auto">
            <h2 className="text-3xl font-bold tracking-tighter sm:text-4xl md:text-5xl text-center mb-8">Key Features</h2>
            <div className="grid gap-10 sm:grid-cols-2 md:grid-cols-3">
              <FeatureCard
                icon={<Palette className="h-10 w-10 text-blue-500" />}
                title="Customizable Display Traits"
                description="Support for custom types via fmt::Display<T>"
              />
              <FeatureCard
                icon={<Box className="h-10 w-10 text-green-500" />}
                title="Standard Container Support"
                description="Built-in display for std::vector, std::set, std::map, and more"
              />
              <FeatureCard
                icon={<Terminal className="h-10 w-10 text-purple-500" />}
                title="ANSI Colors"
                description="Add color and formatting to your outputs"
              />
              <FeatureCard
                icon={<Zap className="h-10 w-10 text-yellow-500" />}
                title="Compact Large Outputs"
                description="Smart printing for large containers"
              />
              <FeatureCard
                icon={<Shield className="h-10 w-10 text-red-500" />}
                title="Safe String Formatting"
                description="Utility for safe string formatting with fmt::format_string"
              />
              <FeatureCard
                icon={<Code className="h-10 w-10 text-indigo-500" />}
                title="Runtime Type Safety"
                description="Optional compile-time checks for unsupported types"
              />
            </div>
          </div>
        </section>
        <section id="examples" className="w-full py-12 md:py-24 lg:py-32">
          <div className="container px-4 md:px-6 mx-auto w-full">
            <h2 className="text-3xl font-bold tracking-tighter sm:text-4xl md:text-5xl text-center mb-8">Code Examples</h2>
            <div className="grid gap-6 items-start w-full">
              <CodeArea
                title="Basic output with colors"
                code={`fmt::println(ansi::blue, "Hello, ", ansi::green, "World", ansi::reset, "!");`}
              />
              <CodeArea
                title="Custom display trait for a struct"
                code={`struct Point {
    int x, y;
};

template<>
struct fmt::Display<Point> {
    static std::string print(const Point& p) {
        return fmt::format_string("Point(%d, %d)", p.x, p.y);
    }
};

Point p{10, 20};
fmt::println("Point: ", p);  // Output: Point: Point(10, 20)`}
              />
              <CodeArea
                title="Printing containers"
                code={`std::vector<int> numbers = {1, 2, 3, 4, 5};
std::map<std::string, int> scores = {{"Alice", 100}, {"Bob", 85}};
std::set<std::string> names = {"John", "Jane", "Alice"};

fmt::println("Vector: ", numbers);
fmt::println("Map: ", scores);
fmt::println("Set: ", names);`}
              />
            </div>
          </div>
        </section>
        <section id="installation" className="w-full py-12 md:py-24 lg:py-32 bg-gray-100 dark:bg-gray-800">
          <div className="container px-4 md:px-6 mx-auto">
            <h2 className="text-3xl font-bold tracking-tighter sm:text-4xl md:text-5xl text-center mb-8">Installation</h2>
            <div className="max-w-2xl mx-auto">
              <CodeArea
                title="Clone and run"
                code={`git clone https://github.com/thefcraft/fmt-display-cpp.git
cd fmt-display-cpp
cp -r fmt {your-project-path}`}
              />
              <p className="mt-4 text-gray-500 dark:text-gray-400">
                After installation, include the library in your project:
              </p>
              <CodeArea
                title="Include headers"
                code={`#include "fmt/display.h"
#include "fmt/vector.h"
#include "fmt/set.h"
// ... other headers as needed`}
              />
            </div>
          </div>
        </section>
      </main>
      <footer className="flex flex-col gap-2 sm:flex-row py-6 w-full shrink-0 items-center px-4 md:px-6 border-t">
        <p className="text-xs text-gray-500 dark:text-gray-400">© 2024 fmt-display-cpp. All rights reserved.</p>
        <nav className="sm:ml-auto flex gap-4 sm:gap-6">
          <Link className="text-xs hover:text-blue-600 transition-colors" href="https://github.com/thefcraft/fmt-display-cpp">
            <Github className="h-4 w-4" />
            <span className="sr-only">GitHub</span>
          </Link>
          <Link className="text-xs hover:text-blue-600 transition-colors" href="#">
            License
          </Link>
        </nav>
      </footer>
    </div>
  )
}

function FeatureCard({ icon, title, description }: { icon: React.JSX.Element, title: string, description: string }) {
  return (
    <div className="flex flex-col items-center space-y-2 border border-gray-200 p-4 rounded-lg transition-all hover:shadow-md">
      {icon}
      <h3 className="text-xl font-bold">{title}</h3>
      <p className="text-sm text-gray-500 dark:text-gray-400 text-center">{description}</p>
    </div>
  )
}


function CodeArea({ title, code }: {title: string, code: string}) {
  return (
    <div className="group relative rounded-lg border p-6 hover:border-blue-300 transition-all w-full overflow-auto">
      <h3 className="text-lg font-semibold mb-2 w-full">{title}</h3>
   
      <CodeBlock header
        code={code}
      />
    </div>
    
  )
}

