#include "lexer.h"

string tokenTypeToString(TokenType type){
    switch(type){
        case IDENTIFIER: return "IDENTIFIER";
        case NUMBER: return "NUMBER";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case ASSIGN: return "ASSIGN";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        // case SEMICOLON: return "SEMICOLON";
        default: return "UNKNOWN";
    }
}

// converting the code into tokens
vector<Token> lexer(const string& code){
    vector<Token> tokens;
    int i = 0, n = code.size();
    
    while(i < n){
        //Removing the Whitespaces
        if(isspace(code[i])) {
            i++;
            continue;
        }

        // if(code[i] == ';') {
        //     tokens.push_back({SEMICOLON, ";"});
        //     i++;
        //     continue;
        // }

        // identifiers, first letter checking whether it is character or not because identifier cant start with number.
        if(isalpha(code[i])) {
            string value = "";
            while (i < n && (isalnum(code[i]) || code[i] == '_')) {
                value += code[i];
                i++;
            }
            tokens.push_back({IDENTIFIER, value});
            continue;
        }

        // NUMBER
        if (isdigit(code[i])) {
            string value = "";
            while ( i < n && isdigit(code[i])) {
                value += code[i];
                i++;
            }
            tokens.push_back({NUMBER, value});
            continue;
        }

        //OPERATORS
        
        if (code[i] == '+') tokens.push_back({PLUS, "+"});
        else if (code[i] == '-') tokens.push_back({MINUS, "-"});
        else if (code[i] == '*') tokens.push_back({MUL, "*"});
        else if (code[i] == '/') tokens.push_back({DIV, "/"});
        else if (code[i] == '=') tokens.push_back({ASSIGN, "="});
        else if (code[i]=='(') tokens.push_back({LPAREN, "("});
        else if(code[i] == ')') tokens.push_back({RPAREN, ")"});
        else {
            cout<< "Error: Invalid character -> " << code[i] <<endl;
            exit(1);
        }

        i++;
    }
    return tokens;
}
