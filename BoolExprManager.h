#ifndef BOOLEXPRMANAGER_H
#define BOOLEXPRMANAGER_H
#include <vector>
#include <string>

#include "BoolExpr.h"

using namespace std;


class BoolExprManager{
public:
    BoolExprManager() = default;
    //distruttore
    ~BoolExprManager() {
        auto i = allocated.begin();
        for (; i != allocated.end(); i++) {
            delete(*i);
        }
    }

    BoolExprManager(const BoolExprManager& other) = delete;
    BoolExprManager& operator=(const BoolExprManager& other) = delete;
    
    //metodi per allocare gli oggetti di tipo BoolExpr
    BoolExpr* makeRelOp(RelOp::OpCode_RelOp op, NumExpr* first, NumExpr* second) {
        BoolExpr* br = new RelOp(op, first, second);
        allocated.push_back(br);
        return br;
    }

    BoolExpr* makeBoolConst(BoolConst::OpCode_BoolConst op) {
        BoolExpr* bconst = new BoolConst(op);
        allocated.push_back(bconst);
        return bconst;
    }

    BoolExpr* makeBoolOp(BoolOp::OpCode_BoolOp op, BoolExpr* first, BoolExpr* second) {
        BoolExpr* bop = new BoolOp(op, first, second);
        allocated.push_back(bop);
        return bop;
    }

private:
    vector<BoolExpr*> allocated;


};


#endif