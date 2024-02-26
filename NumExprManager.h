#ifndef NUMEXPRMANAGER_H
#define NUMEXPRMANAGER_H
#include <vector>

#include "NumExpr.h"

class NumExprManager {
public:
    NumExprManager() = default;

    //distruttore
    ~NumExprManager() {
        auto i = allocated.begin();
        for (; i != allocated.end(); i++) {
            delete(*i);
        }
    }

    NumExprManager(const NumExprManager& other) = delete;
    NumExprManager& operator= (const NumExprManager& other) = delete;


    ////metodi per allocare gli oggetti di tipo NumExpr
    NumExpr* makeNumber(int64_t value) {
        NumExpr* n = new Number(value);
        allocated.push_back(n);
        return n;
    }

    NumExpr* makeVariable(string v, int64_t value) {
        NumExpr* var = new Variable(v, value);
        allocated.push_back(var);
        return var;
    }

    NumExpr* makeOperator(Operator::OpCode_Operator op, NumExpr* first, NumExpr* second) {
        NumExpr* ope = new Operator(op, first, second);
        allocated.push_back(ope);
        return ope;
    }
private:
    vector<NumExpr*> allocated;
};

#endif
