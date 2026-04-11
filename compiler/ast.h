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

inline string astToJson(ASTNode* node) {
    if (!node) return "";

    string json = "{";
    json += "\"type\":\"" + node->type + "\",";
    json += "\"value\":\"" + node->value + "\"";

    if (node->left) {
        json += ",\"left\":" + astToJson(node->left);
    }

    if (node->right) {
        json += ",\"right\":" + astToJson(node->right);
    }

    json += "}";
    
    return json;
}

#endif


