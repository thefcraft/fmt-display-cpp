import { Button } from "@/components/ui/button"
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card"
import { Github, MessageCircle, Bug } from 'lucide-react'
import { Header } from "@/components/header"
import { AppSidebar } from "@/components/app-sidebar"
import { SidebarInset } from "@/components/ui/sidebar"
export default function CommunityPage() {
  return (<>
    <AppSidebar currIndex={7} />
    <SidebarInset className="overflow-auto">
    <Header page="community" />
    <div className="max-w-4xl mx-auto px-4 py-8 w-full">
      <h1 className="text-4xl font-bold mb-6">fmt-display-cpp Community</h1>
      <p className="text-xl text-muted-foreground mb-8">
        Join our community, contribute to the project, and get support for fmt-display-cpp.
      </p>
      
      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id="contribution-guide">Contribution Guide</h2>
        <p className="mb-4">
          We welcome contributions to fmt-display-cpp! Here's how you can get involved:
        </p>
        <ol className="list-decimal pl-6 space-y-2 mb-4">
          <li>Fork the repository on GitHub</li>
          <li>Create a new branch for your feature or bug fix</li>
          <li>Write tests for your changes</li>
          <li>Implement your changes</li>
          <li>Ensure all tests pass</li>
          <li>Submit a pull request with a clear description of your changes</li>
        </ol>
        <p>
          Please make sure to follow our coding standards and commit message conventions. 
          For more detailed information, check out our 
          <a href="https://github.com/thefcraft/fmt-display-cpp/blob/main/CONTRIBUTING.md" className="text-blue-500 hover:underline ml-1">
            contribution guidelines
          </a>.
        </p>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id="community-resources">Community Resources</h2>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
          <Card>
            <CardHeader>
              <CardTitle>GitHub Repository</CardTitle>
              <CardDescription>View source code, report issues, and contribute</CardDescription>
            </CardHeader>
            <CardContent>
              <Button asChild variant="outline" className="w-full">
                <a href="https://github.com/thefcraft/fmt-display-cpp" target="_blank" rel="noopener noreferrer">
                  <Github className="mr-2 h-4 w-4" /> Visit GitHub Repo
                </a>
              </Button>
            </CardContent>
          </Card>
          <Card>
            <CardHeader>
              <CardTitle>Discord Community</CardTitle>
              <CardDescription>Join our Discord server for discussions and support</CardDescription>
            </CardHeader>
            <CardContent>
              {/* <Button asChild variant="outline" className="w-full" disabled> */}
              <Button variant="outline" className="w-full" disabled> 
                {/* <a href="#" target="_blank" rel="noopener noreferrer"> */}
                  <MessageCircle className="mr-2 h-4 w-4" /> Join Discord
                {/* </a> */}
              </Button>
            </CardContent>
          </Card>
        </div>
      </section>

      <section className="mb-12">
        <h2 className="text-2xl font-semibold mb-4" id="report-issues">Report Issues</h2>
        <p className="mb-4">
          If you encounter any bugs or have feature requests, please report them on our GitHub issue tracker:
        </p>
        <Button asChild variant="outline">
          <a href="https://github.com/thefcraft/fmt-display-cpp/issues" target="_blank" rel="noopener noreferrer">
            <Bug className="mr-2 h-4 w-4" /> Report an Issue
          </a>
        </Button>
        <p className="mt-4">
          When reporting issues, please provide as much detail as possible, including:
        </p>
        <ul className="list-disc pl-6 space-y-2">
          <li>A clear and descriptive title</li>
          <li>Steps to reproduce the issue</li>
          <li>Expected behavior</li>
          <li>Actual behavior</li>
          <li>Your environment (OS, compiler version, etc.)</li>
        </ul>
      </section>

      <section>
        <h2 className="text-2xl font-semibold mb-4" id="get-involved">Get Involved</h2>
        <p className="mb-4">
          There are many ways to contribute to fmt-display-cpp beyond code contributions:
        </p>
        <ul className="list-disc pl-6 space-y-2">
          <li>Improve documentation</li>
          <li>Write tutorials or blog posts</li>
          <li>Help answer questions in the community</li>
          <li>Spread the word about fmt-display-cpp</li>
        </ul>
        <p className="mt-4">
          Every contribution, no matter how small, is valuable and appreciated!
        </p>
      </section>
    </div>
    </SidebarInset></>)
}

