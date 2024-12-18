"use client"

import * as React from "react"
import { Code2, Minus, Plus } from "lucide-react"
import { SearchForm } from "@/components/search-form"
import {
  Collapsible,
  CollapsibleContent,
  CollapsibleTrigger,
} from "@/components/ui/collapsible"
import {
  Sidebar,
  SidebarContent,
  SidebarGroup,
  SidebarHeader,
  SidebarMenu,
  SidebarMenuButton,
  SidebarMenuItem,
  SidebarMenuSub,
  SidebarMenuSubButton,
  SidebarMenuSubItem,
  SidebarRail,
} from "@/components/ui/sidebar"


const data = {
  navMain: [
    {
      title: "Introduction",
      url: "#",
      items: [
        {
          title: "Overview",
          url: "/docs/introduction#overview",
        },
        {
          title: "Why Use fmt::display?",
          url: "/docs/introduction#why-use-fmt-display",
        },
      ],
    },
    {
      title: "Getting Started",
      url: "#",
      items: [
        {
          title: "Installation",
          url: "/docs/getting-started#installation",
        },
        {
          title: "Quick Start Guide",
          url: "/docs/getting-started#quick-start-guide",
        },
        {
          title: "Key Concepts",
          url: "/docs/getting-started#key-concepts",
        },
      ],
    },
    {
      title: "Core Features",
      url: "#",
      items: [
        {
          title: "ANSI Styling",
          url: "/docs/core-features#ansi-styling",
        },
        {
          title: "Custom Display Trait",
          url: "/docs/core-features#custom-display-trait",
        },
        {
          title: "Safe String Formatting",
          url: "/docs/core-features#safe-string-formatting",
        },
        {
          title: "fmtout Class",
          url: "/docs/core-features#fmtout-class",
        },
        {
          title: "PrintFormatter Utility",
          url: "/docs/core-features#printformatter-utility",
        },
        {
          title: "Global Print Instances",
          url: "/docs/core-features#global-print-instances",
        },
      ],
    },
    {
      title: "Advanced Topics",
      url: "#",
      items: [
        {
          title: "Custom Type Specialization",
          url: "/docs/advanced-topics#custom-type-specialization",
        },
        {
          title: "Error Handling",
          url: "/docs/advanced-topics#error-handling",
        },
        {
          title: "Compile-Time Type Checks",
          url: "/docs/advanced-topics#compile-time-type-checks",
        },
        {
          title: "Extending fmt::display",
          url: "/docs/advanced-topics#extending-fmt-display",
        },
      ],
    },
    {
      title: "API Reference",
      url: "#",
      items: [
        {
          title: "Display Trait",
          url: "/docs/api-reference#display-trait",
        },
        {
          title: "fmtout Methods",
          url: "/docs/api-reference#fmtout-methods",
        },
        {
          title: "PrintFormatter Methods",
          url: "/docs/api-reference#printformatter-methods",
        },
        {
          title: "ANSI Namespace Constants",
          url: "/docs/api-reference#ansi-namespace-constants",
        },
        {
          title: "Helper Functions",
          url: "/docs/api-reference#helper-functions",
        },
      ],
    },
    {
      title: "Examples",
      url: "#",
      items: [
        {
          title: "Simple Output Example",
          url: "/docs/examples#simple-output-example",
        },
        {
          title: "Custom Type Example",
          url: "/docs/examples#custom-type-example",
        },
        {
          title: "Styled Output Example",
          url: "/docs/examples#styled-output-example",
        },
        {
          title: "Error Handling Example",
          url: "/docs/examples#error-handling-example",
        },
      ],
    },
    {
      title: "Community",
      url: "#",
      items: [
        {
          title: "Contribution Guide",
          url: "/docs/community#contribution-guide",
        },
        {
          title: "Community Resources",
          url: "/docs/community#community-resources",
        },
        {
          title: "Report Issues",
          url: "/docs/community#report-issues",
        },
      ],
    },
  ],
}
interface AppSidebarProps extends  React.ComponentProps<typeof Sidebar>{
  currIndex?: number
};
export function AppSidebar({ currIndex, ...props }: AppSidebarProps) {
  return (
    <Sidebar {...props}>
      <SidebarHeader>
        <SidebarMenu>
          <SidebarMenuItem>
            <SidebarMenuButton size="lg" asChild>
              <a href="/docs">
                <div className="flex aspect-square size-8 items-center justify-center rounded-lg bg-sidebar-primary text-sidebar-primary-foreground">
                  <Code2 className="size-4" />
                </div>
                <div className="flex flex-col gap-0.5 leading-none">
                  <span className="font-semibold">Documentation</span>
                  <span className="">v1.0.0</span>
                </div>
              </a>
            </SidebarMenuButton>
          </SidebarMenuItem>
        </SidebarMenu>
        <SearchForm />
      </SidebarHeader>
      <SidebarContent>
        <SidebarGroup>
          <SidebarMenu>
            {data.navMain.map((item, index) => (
              <Collapsible
                key={item.title}
                defaultOpen={currIndex?index === currIndex-1:undefined}
                className="group/collapsible"
              >
                <SidebarMenuItem>
                  <CollapsibleTrigger asChild>
                    <SidebarMenuButton>
                      {item.title}{" "}
                      <Plus className="ml-auto group-data-[state=open]/collapsible:hidden" />
                      <Minus className="ml-auto group-data-[state=closed]/collapsible:hidden" />
                    </SidebarMenuButton>
                  </CollapsibleTrigger>
                  {item.items?.length ? (
                    <CollapsibleContent>
                      <SidebarMenuSub>
                        {item.items.map((item) => (
                          <SidebarMenuSubItem key={item.title}>
                            <SidebarMenuSubButton
                              asChild
                              // isActive={item.isActive}
                            >
                              <a href={item.url} className="min-h-7 h-fit">{item.title}</a>
                            </SidebarMenuSubButton>
                          </SidebarMenuSubItem>
                        ))}
                      </SidebarMenuSub>
                    </CollapsibleContent>
                  ) : null}
                </SidebarMenuItem>
              </Collapsible>
            ))}
          </SidebarMenu>
        </SidebarGroup>
      </SidebarContent>
      <SidebarRail />
    </Sidebar>
  )
}
