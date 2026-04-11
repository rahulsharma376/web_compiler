import { spawn } from "child_process";

export async function POST(req) {
    try {
        const { code } = await req.json();

        return new Promise((resolve) => {
            const process = spawn("./compiler.exe");

            let output = "";
            let error = "";

            process.stdin.write(code);
            process.stdin.end();

            process.stdout.on("data", (data) => {
                output += data.toString();
            });

            process.stderr.on("data", (data) => {
                error += data.toString();
            });

            process.on("close", () => {
                resolve(
                    new Response(
                        JSON.stringify({
                            raw: output,
                            error: error
                        }),
                        { status: 200 }
                    )
                );
            });
        });

    } catch (err) {
        return new Response(
            JSON.stringify({ error: err.message }),
            { status: 500 }
        );
    }
}