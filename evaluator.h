#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ast.h"
#include <unordered_map>

class Evaluator {
    std::unordered_map<std::string, int> variables;

    public:
        int evaluate(ASTNode* node);
};

#endif