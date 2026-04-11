#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "evaluator.h"
#include <iostream>

using namespace std;

void printAST(ASTNode* node, int depth = 0){
    if (!node) return;

    for(int i = 0; i < depth; i++) cout << " ";
    
    cout << node->type << "(" << node->value << ")" <<endl;
    
    printAST(node->left, depth+1);
    printAST(node->right, depth+1);
}

int main() {
    // string code = "a = 5 + 3 * 2";

    string line, code;
    while(getline(cin, line)) {
        code += line + " ";
    }

    // string code;
    // getline(cin, code);
    
    // string code(
    //     (istreambuf_iterator<char>(cin)),
    //     istreambuf_iterator<char>()
    // );

    //convert newline -> Space
    for (char &c : code) {
        if (c == '\n') c = ' ';
    }

    // converting new line to space

    // for (char &c: code){
    //     if (c == '\n' ) c = ' ';
    // }

    vector<Token> tokens = lexer(code);

    // Parser parser(tokens); //class Parser with constructer parser 
    // ASTNode* root = parser.parseAssignment();

    // printAST(root);


    // Evaluator evaluator;

    // int result = evaluator.evaluate(root);

    // cout <<"\nResult: " << result << endl;


    Parser parser(tokens);
    vector<ASTNode*> program = parser.parseProgram();

    Evaluator evaluator;

    for (auto stmt: program) {
        // printAST(stmt);

        int result = evaluator.evaluate(stmt);    //for total output
        cout << result << endl;     // Abstract Syntax tree

        cout<< astToJson(stmt) << endl;
    }

    return 0;
}