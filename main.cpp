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
    string code = "a = 5 + 3 * 2";

    vector<Token> tokens = lexer(code);

    Parser parser(tokens); //class Parser with constructer parser 
    ASTNode* root = parser.parseAssignment();

    printAST(root);


    Evaluator evaluator;

    int result = evaluator.evaluate(root);

    cout <<"\nResult: " << result << endl;

    return 0;
}