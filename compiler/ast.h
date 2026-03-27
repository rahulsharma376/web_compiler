#ifndef AST_H
#define AST_H

#include<bits/stdc++.h>
using namespace std;

struct ASTNode{
    string type;
    string value;

    ASTNode* left;
    ASTNode* right;

    ASTNode(string t, string v)
        : type(t), value(v), left(nullptr), right(nullptr) {}
};

#endif
