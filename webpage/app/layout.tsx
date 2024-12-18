import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

const url = 'https://fmt-display-cpp.thefcraft.site'
export const metadata = {
  title: "fmt-display-cpp - Modern C++ Formatting Library",
  description:
    "fmt-display-cpp is a modern C++ library for enhanced text formatting and custom display traits. Simplify your console output with ANSI styling, secure formatting, and intuitive tools.",
  authors: [{ name: "ThefCraft" }],
  keywords:
    "C++, text formatting, custom display traits, ANSI styling, C++ library, console applications, CLI tools, debugging, output customization",
  openGraph: {
    title: "fmt-display-cpp - Modern C++ Formatting Library",
    description:
      "A powerful C++ library for custom text formatting, ANSI styling, and intuitive output tools. Simplify and enhance your console applications.",
    url: "https://github.com/thefcraft/fmt-display-cpp",
    type: "website",
    images: [
      {
        url: `${url}/image.png`,
        width: 1200,
        height: 630,
        alt: "fmt-display-cpp banner",
      },
    ],
  },
  twitter: {
    card: "summary_large_image",
    title: "fmt-display-cpp - Modern C++ Formatting Library",
    description:
      "Simplify console output in C++ with custom display traits, ANSI styling, and secure formatted output.",
    images: [`${url}/image.png`],
  },
  icons: {
    icon: `${url}/favicon.ico`,
  },
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body
        className={`${geistSans.variable} ${geistMono.variable} antialiased`}
      >
        {children}
      </body>
    </html>
  );
}
