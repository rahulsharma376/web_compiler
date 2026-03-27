#include "parser.h"
#include <iostream>
using namespace std;

Parser::Parser(vector<Token> t) : tokens(t), pos(0) {}

Token Parser::current() {
    return tokens[pos];
}

void Parser::eat(TokenType type) {
    if (current().type == type) pos++;
    else {
        cout << "Unexpected token\n";
        exit(1);
    }
}

ASTNode* Parser::factor() {
    Token t = current();
    
    if (t.type == NUMBER) {
        eat(NUMBER);
        return new ASTNode("NUMBER", t.value);
    }

    if (t.type == IDENTIFIER) {
        eat(IDENTIFIER);
        return new ASTNode("IDENTIFIER", t.value);
    }

    if (t.type == LPAREN) {
        eat(LPAREN);
        ASTNode* node = expression();
        
        eat(RPAREN);
        return node;
    }

    cout << "Invalid factor\n";
    exit(1);
}


ASTNode* Parser::term() {
    ASTNode* node = factor();

    while(pos < tokens.size() && (current().type == MUL || current().type == DIV)) {

        Token op = current();

        if (op.type == MUL)
            eat(MUL);
        else
            eat(DIV);

        ASTNode* right = factor();

        ASTNode* newNode = new ASTNode("BINARY_OP", op.value);
        newNode->left = node;
        newNode->right = right;

        node = newNode;
    }

    return node;
}

ASTNode* Parser::expression() {
    ASTNode* node = term();

    while (pos < tokens.size() && (current().type == PLUS || current().type == MINUS)) {
        
        Token op = current();

        if (op.type == PLUS)
            eat(PLUS);
        else
            eat(MINUS);

        ASTNode* right = term();
        
        ASTNode* newNode = new ASTNode("BINARY_OP", op.value);
        newNode->left = node;
        newNode->right = right;
        
        node = newNode;

    }
    return node;
}


ASTNode* Parser::parseAssignment() {
    ASTNode* left = factor();

    if (pos < tokens.size() && current().type == ASSIGN) {
        eat(ASSIGN);
        ASTNode* right = expression();

        ASTNode* node = new ASTNode("ASSIGN", "=");
        node->left = left;
        node->right = right;
        
        return node;
    }
}