#ifndef LEXER_H
#define LEXER_H

#include <bits/stdc++.h>
using namespace std;

enum TokenType {
    IDENTIFIER,
    NUMBER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    ASSIGN,
    LPAREN,
    RPAREN
};

struct Token {
    TokenType type;
    string value;
};

vector<Token> lexer(const string& code);

string tokenTypeToString(TokenType type);

#endif