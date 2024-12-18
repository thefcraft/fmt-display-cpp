"use client";

import React, { useState } from "react";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import { atomDark } from "react-syntax-highlighter/dist/esm/styles/prism";
import { Check, Copy } from "lucide-react";

interface CodeBlockProps {
  title?: string;
  language?: string;
  code: string;
  header?: boolean
}

function CodeBlock({ title, language, code, header }: CodeBlockProps) {
  const [copied, setCopied] = useState(false);

  const copyToClipboard = () => {
    navigator.clipboard.writeText(code).then(() => {
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    });
  };

  return (
    <div className="rounded-lg overflow-hidden">
      {(header || title) && (
        <div className="bg-gray-800 text-white px-4 py-2 flex justify-between items-center">
          <span>{title?title:"example."}{title?"":(language?language: "cpp")}</span>
          <button
            onClick={copyToClipboard}
            className="text-gray-300 hover:text-white focus:outline-none"
          >
            {copied ? <Check size={20} /> : <Copy size={20} />}
          </button>
        </div>
      )} 
      <SyntaxHighlighter
        language={language?language: "cpp"}
        style={atomDark}
        customStyle={{
          margin: 0,
          borderRadius: (header || title) ? "0 0 0.5rem 0.5rem" : "0.5rem",
        }}
      >
        {code}
      </SyntaxHighlighter>
    </div>
  );
}

interface InlineCodeProps {
  children: React.ReactNode;
}

function InlineCode({ children }: InlineCodeProps) {
  return (
    <code className="bg-gray-100 text-gray-800 rounded px-1 py-0.5 font-mono text-sm">
      {children}
    </code>
  );
}

export {CodeBlock, InlineCode};