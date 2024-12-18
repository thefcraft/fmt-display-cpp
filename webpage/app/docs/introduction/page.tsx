import { Header } from "@/components/header"
import { AppSidebar } from "@/components/app-sidebar"
import {
  SidebarInset
} from "@/components/ui/sidebar"

export default function IntroductionPage() {
    return (<>
    <AppSidebar currIndex={1} />
    <SidebarInset className="overflow-auto">
    <Header page="introduction"/>
    <div className="max-w-4xl mx-auto px-4 py-8">
        <h1 className="text-4xl font-bold">Introduction to fmt-display-cpp</h1>
        
        <section id="overview">
          <h2 className="text-2xl font-semibold mt-8 mb-4" id="overview">Overview</h2>
          <p>
            fmt-display-cpp is a modern C++ library designed to simplify the process of formatting and displaying objects and containers. It provides a flexible and intuitive API for customizing how your types are displayed, making it easier to create readable and well-formatted output in your C++ applications.
          </p>
        </section>
  
        <section id="why-use-fmt-display">
          <h2 className="text-2xl font-semibold mt-8 mb-4" id="why-use-fmt-display">Why Use fmt::display?</h2>
          <ul className="list-disc pl-6 space-y-2">
            <li>Easy-to-use API for customizing object display</li>
            <li>Built-in support for standard containers</li>
            <li>ANSI color and styling support for rich console output</li>
            <li>Type-safe string formatting</li>
            <li>Compile-time type checking to catch errors early</li>
            <li>Extensible design allowing for easy integration with custom types</li>
          </ul>
          <p className="mt-4">
            Whether you're building a command-line application, debugging complex data structures, or simply want more control over how your objects are displayed, fmt-display-cpp provides the tools you need to create clear, customized output with minimal effort.
          </p>
        </section>
      </div>
      </SidebarInset>
      </>)
  }
  
  