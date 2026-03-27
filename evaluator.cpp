#include "evaluator.h"
#include <iostream>
using namespace std;

int Evaluator::evaluate(ASTNode* node) {
    
    if (node->type == "NUMBER") {
        return stoi(node->value);
    }

    if(node->type == "IDENTIFIER") {
        if (variables.find(node->value) != variables.end())
            return variables[node->value];
        
        cout << "Undefined variable: " << node->value << endl;
        exit(1);
    }

    if (node->type == "BINARY_OP") {
        int left = evaluate(node->left);
        int right = evaluate(node->right);

        if (node->value == "+") return left+right;
        if (node->value == "-") return left-right;
        if (node->value == "*") return left*right;
        if (node->value == "/") return left/right;
    }

    if(node->type == "ASSIGN"){
        string varName = node->left->value;
        int val = evaluate(node->right);

        variables[varName] = val;

        return val;
    }

    cout << "Invalid AST Node\n";
    exit(1);
}