import {
    SidebarProvider,
} from "@/components/ui/sidebar"


export default function DocsLayout({
  children,
}: {
  children: React.ReactNode
}) {
  return (
    <SidebarProvider>
      {/* <AppSidebar /> */}
      {/* <SidebarInset className="overflow-auto"> */}
        {children}
      {/* </SidebarInset> */}
    </SidebarProvider>
  )
}

