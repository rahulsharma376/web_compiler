#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

class Parser {
    vector<Token> tokens;
    int pos;

    public:
        Parser(vector<Token> t);

        Token current();
        void eat(TokenType type);

        ASTNode* factor();
        ASTNode* term();
        ASTNode* expression();
        ASTNode* parseAssignment();

        vector<ASTNode*> parseProgram();

    };

#endif