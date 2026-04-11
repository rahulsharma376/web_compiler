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

        const parsedList = lines.map((line: string) => {
            try {
                return JSON.parse(line);
            } catch {
                return null;
            }
        }).filter(Boolean);

        setAst(parsedList);
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

    

    const renderTree = (node: any) => {
        if(!node) return null;

        return (
            <div style={{ textAlign: "center", marginTop: "40px"}}>

                {/*root node or node, parent node */}
                <div style={{
                    display: "inline-block",
                    padding: "6px 12px",
                    background: "#1e293b",
                    borderRadius: "8px",
                    border: "1px solid #334155"
                }}>
                    {node.type} ({node.value})
                </div>

                {/*Child node or children */}
                {(node.left || node.right) && (
                    <div style={{ position: "relative", marginTop: "30px" }}>

                        {/*SVG part for the lining */}
                        <svg 
                            width="240"
                            height="60"
                            style={{
                                position: "absolute",
                                top: "-10px",
                                left: "50%",
                                transform: "translate(-50%)"
                            }}
                        >
                            {node.left && <Line x1="120" y1="0" x2="40" y2="50" />}
                            {node.right && <Line x1="120" y1="0" x2="200" y2="50" />}
                        </svg>

                        <div style={{
                            display: "flex", 
                            justifyContent: "space-between",
                            width: "200px",
                            margin: "auto"
                        }}>
                            <div style={{width: "80px"}}>
                                {node.left && renderTree(node.left)}
                            </div>
                            
                            <div style={{width: "80px"}}>
                                {node.right && renderTree(node.right)}
                            </div>

                        </div>

                    </div>
                )}

            </div>
        );
    };
    return (
        <div style = {{
            minHeight: "100vh",
            background: "#0f172a",
            color: "white",
            padding: "30px",
            fontFamily: "monospace"
        }}>

            <h1 style={{ fontSize: "28px", marginBottom: "20px" }}>
                    Self Made Custom Interpreter
            </h1>

            <textarea
                value= {code}
                onChange={(e) => setCode(e.target.value)}
                placeholder="Write your code here..."
                style={{
                    width: "100%",
                    height: "200px",
                    background: "#1e293b",
                    color: "white",
                    border: "1px solid #334155",
                    padding: "10px",
                    borderRadius: "8px"
                }}
            />

            <br /><br />

            <button
                onClick={runCode}
                disabled = {loading}
                style = {{
                    padding: "10px 20px",
                    background: "#3b82f6",
                    border: "none",
                    borderRadius: "6px",
                    color: "white",
                    cursor: "pointer"
                }}>

                {loading ? "Running..." : "Run Code"}
            
            </button>

            <h3 style={{ marginTop: "20px" }}> AST: </h3>
            
            <div style={{
                background: "#020617",
                padding: "20px",
                borderRadius: "10px",
                marginTop: "10px",
                border: "1px solid #334155",
                overflowX: "auto",
                textAlign: "center",
                maxWidth: "900px",
                margin: "auto"
            }}>
                {ast.length > 0 ? (
                    ast.map((tree, index) => (
                        <div key = {index} style={{ marginBottom: "50px"}}>
                            {renderTree(tree)}
                        </div>
                    ))
                ): "No AST yet"}
            </div>

        </div>
    );
}