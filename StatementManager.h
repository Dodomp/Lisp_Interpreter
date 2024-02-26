#ifndef STATEMENTMANAGER_H
#define STATEMENTMANAGER_H

#include <vector>

#include "Statement.h"
#include "NumExpr.h"

using namespace std;

class StatementManager {
public:
    StatementManager() = default;

    //distruttore
    ~StatementManager() {
        auto i = allocated.begin();
        for (; i != allocated.end(); i++) {
            delete(*i);
        }
    }

    
    StatementManager(const StatementManager& other) = delete;
    StatementManager& operator=(const StatementManager& other) = delete;

    Statement* makePrintStmt(NumExpr* element) {
        Statement* prin = new PrintStmt(element);
        allocated.push_back(prin);
        return prin;
    }

    //metodi per creare oggetti di tipo Statement
    Statement* makeSetStmt(Variable* first, NumExpr* second) {
        Statement* set = new SetStmt(first, second);
        allocated.push_back(set);
        return set;
    }

    Statement* makeInputStmt(Variable* element) {
        Statement* input = new InputStmt(element);
        allocated.push_back(input);
        return input;
    }

    Statement* makeWhileStmt(BoolExpr* first, Block* second) {
        Statement* wh = new WhileStmt(first, second);
        allocated.push_back(wh);
        return wh;
    }

    Statement* makeIfStmt(BoolExpr* first, Block* second, Block* third) {
        Statement* ifs = new IfStmt(first, second, third);
        allocated.push_back(ifs);
        return ifs;
    }

private:
    vector <Statement*> allocated;
};


#endif
