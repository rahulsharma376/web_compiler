"use client";

import { useState } from "react";

export default function Home() {
    const [code, setCode] = useState("");
    const [output, setOutput] = useState("");
    const [loading, setLoading] = useState(false);
    const [ast, setAst] = useState<any[]>([]);

    const runCode = async () => {
        setLoading(true);

        const res = await fetch("/api/run", {
            method: "POST",
            body: JSON.stringify({ code })
        });

        const data = await res.json();

        

        const lines = data.raw.trim().split("\n");

        let results: any[] = [];

        for (let i = 0; i < lines.length; i += 2) {
            const result = lines[i];
            const astLine = lines[i+1];

            try {
                const astObj = JSON.parse(astLine);
                results.push({
                    result,
                    ast: astObj
                });
            } catch {
                // Nothing to print
            }
        }
        setAst(results);

        setOutput("");

        setLoading(false);
    };

    const Line = ({ x1, y1, x2, y2}: any) => (
        <line 
            x1 = {x1}
            y1 = {y1}
            x2 = {x2}
            y2 = {y2}
            stroke ="#64748b"
            strokeWidth= "2"
        />
    );

    

    // 
    

    const renderTree = (node: any) => {
        if (!node) return null;

        const getColor = (type: string) => {
            if(type === "NUMBER") return "#22c55e";
            if(type === "IDENTIFIER") return "#38bdf8";
            if(type === "BINARY_OP") return "#f59e0b";
            if(type === "ASSIGN") return "#a78bfa";
            return "#e2e8f0";
        }

        return (
            <div style={{ display: "flex", flexDirection: "column", alignItems: "center"}}>
                
                {/* Node or root branch*/}
                <div style={{
                    padding: "6px 12px",
                    background: node.type === "NUMBER" ? "#064e3b" :
                                node.type === "IDENTIFIER" ? "#0c4a6e" :
                                node.type === "BINARY_OP" ? "#78350f" :
                                node.type === "ASSIGN" ? "#4c1d95" :
                                "#1e293b",
                    borderRadius: "8px",
                    border: "1px solid #334155",
                    color: "#e2e8f0",
                    boxShadow: "0 2px 6px rgba(0,0,0,0.4)"
                }}>
                    <span style={{ color: getColor(node.type) }}>
                        {node.type} ({node.value})
                    </span>
                </div>

                { /* lines, Child node (node from the parent branch) */}

                {(node.left || node.right) && (
                    <>
                        {/* lines */}
                        <svg width="100%" height="40">
                            {node.left && (
                                <line
                                    x1 = "50%"
                                    y1 = "0"
                                    x2 = "25%"
                                    y2 = "40"
                                    stroke = "#64748b"
                                    strokeWidth="2"
                                />
                            )}

                            {node.right && (
                                <line 
                                    x1 = "50%"
                                    y1 = "0"
                                    x2 = "75%"
                                    y2 = "40"
                                    stroke = "#64748b"
                                    strokeWidth= "2"
                                />
                            )}
                        </svg>

                        {/*Child node */}
                        <div style={{
                            display: "flex",
                            justifyContent: "space-between",
                            width: "100%",
                            gap: "10px"
                        }}>
                            <div style={{ flex: 1, display: "flex", justifyContent: "center"}}>
                                {node.left && renderTree(node.left)}
                            </div>

                            <div style={{ flex: 1, display: "flex", justifyContent: "center"}}>
                                {node.right && renderTree(node.right)}
                            </div>
                        </div>

                    </>
                )}

            </div>
        )
    }

    return (
        <div style = {{
            minHeight: "100vh",
            background: "linear-gradient(135deg, #1f2937, #111827)",
            color: "#e2e8f0",
            padding: "30px",
            fontFamily: "monospace"
        }}>

            <h1 style={{
                fontSize: "30px",
                marginBottom: "20px",
                fontWeight: "700",
                letterSpacing: "1px",
                color: "#f1f5f9" 
            }}>
                Mathematical Interpreter with AST Evaluation
            </h1>

            <textarea
                value= {code}
                onChange={(e) => setCode(e.target.value)}
                placeholder="Write your code here..."
                style={{
                    width: "100%",
                    height: "200px",
                    background: "rgba(15, 23, 42, 0.6)",
                    backdropFilter: "blue(8px)",
                    color: "#e2e8f0",
                    border: "1px solid rgba(255,255,255,0.1)",
                    padding: "10px",
                    borderRadius: "8px",
                    outline: "none",
                    fontSize: "14px",
                    boxShadow: "0 0 10px rgba(56,189, 248, 0.2)"
                }}
            />

            <br /><br />

            <button
                onClick={runCode}
                disabled = {loading}
                style = {{
                    padding: "10px 20px",
                    background: "#38bdf8",
                    // background: "linear-gradient(135deg, #38bdf8, #6366f1)",
                    // color: "white",
                    border: "none",
                    borderRadius: "6px",
                    color: "#020617",
                    fontWeight: "600",
                    cursor: "pointer"
                }}>

                {loading ? "Running..." : "Run Code"}
            
            </button>

            <h2 style={{ 
                marginTop: "30px",
                textAlign: "center",
                fontSize: "22px",
                fontWeight: "700",
                marginBottom: "10px",
                color: "#38bdf8",
                letterSpacing: "1px"
            }}>
                AST Visualization: 
            </h2>
            
            <div style={{
                background: "rgba(2,6,23,0.85)",
                backdropFilter: "blur(10px)",
                padding: "20px",
                borderRadius: "10px",
                marginTop: "10px",
                border: "1px solid rgba(255,255,255,0.08)",
                overflowX: "auto",
                textAlign: "center",
                width: "100%",
                maxWidth: "900px",
                margin: "20px auto"
            }}>
                {ast.length > 0 ? (
                    ast.map((item, index) => (
                        <div key={index} style={{ marginBottom: "50px"}}>

                            <div style={{
                                marginBottom: "10px",
                                fontSize: "16px",
                                color: "#22c55e"
                            }}> 
                                Result: {item.result}
                            </div>

                            {renderTree(item.ast)}
                        </div>
                    ))
                ): "No AST yet"}
            </div>

        </div>
    );
}