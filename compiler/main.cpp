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
        printAST(stmt);
        int result = evaluator.evaluate(stmt);
        cout << "Result: " << result << endl;
    }

    return 0;
}