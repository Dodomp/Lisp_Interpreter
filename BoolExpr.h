#ifndef BOOLEXPR_H
#define BOOLEXPR_H

#include <string>

#include "NumExpr.h"

using namespace std;

class Visitor;

//la classe BoolExpr è costituita da 3 sottoclassi
//creo la classe virtuale genitore e poi le tre classi figli che erediteranno dal genitore



//classe virtuale
class BoolExpr {
public:
    virtual ~BoolExpr() {};

    //metodo virutale per effettuare la visita dell'albero
    virtual int64_t accept(Visitor* v) = 0;
};

//I classe figlio
class RelOp : public BoolExpr {
public:
    enum OpCode_RelOp {LT, GT, EQ};

    RelOp(OpCode_RelOp op, NumExpr* first, NumExpr* second) : _op{ op }, _first{ first }, _second{ second } {};
    ~RelOp() = default;
    RelOp(const RelOp& other) = default;
    RelOp& operator=(const RelOp& other) = default;

    //getters
    OpCode_RelOp get_op()const {
        return _op;
    }
    NumExpr* get_first()const {
        return _first;
    }
    NumExpr* get_second()const {
        return _second;
    }

    static OpCode_RelOp stringToOpCode_Operator(string s) {
        if (s == "LT")		return LT;
        else if (s == "GT") return GT;
        else if (s == "EQ") return EQ;
    }

    //metodo concreto per effettuare la visita dell'albero
    int64_t accept(Visitor* v) override;

private:

    OpCode_RelOp _op;
    NumExpr* _first;
    NumExpr* _second;
};

//II classe figlio
class BoolConst :public BoolExpr {
public:
    enum OpCode_BoolConst { TRUE, FALSE};

    BoolConst(OpCode_BoolConst op) : _op{ op } {};
    ~BoolConst() = default;
    BoolConst(const BoolConst& other) = default;
    BoolConst& operator=(const BoolConst& other) = default;

    OpCode_BoolConst get_lop()const {
        return _op;
    }
    static OpCode_BoolConst stringToOpCode_Operator(std::string s) {
        if (s == "TRUE")	return TRUE;
        else if (s == "FALSE") return FALSE;
    }

    //metodo concreto per la visita dell'albero
    int64_t accept(Visitor* v) override;

private:
    OpCode_BoolConst _op;
};


//III classe figlio
class BoolOp : public BoolExpr {
public:
    enum OpCode_BoolOp {AND, OR, NOT};

    BoolOp(OpCode_BoolOp op, BoolExpr* first, BoolExpr* second) : _op{ op }, _first{ first }, _second{ second } {};
    ~BoolOp() = default;
    BoolOp(const BoolOp& other) = default;
    BoolOp& operator=(const BoolOp& other) = default;

    OpCode_BoolOp get_op()const {
        return _op;
    }
    BoolExpr* get_first()const {
        return _first;
    }
    BoolExpr* get_second()const {
        return _second;
    }
    static OpCode_BoolOp stringToOpCode_Operator(std::string s) {
        if (s == "AND")		return AND;
        else if (s == "OR") return OR;
        else if (s == "NOT") return NOT;
    }

    //metodo concreto per la visita dell'albero
    int64_t accept(Visitor* v) override;

private:
    OpCode_BoolOp _op;
    BoolExpr* _first;
    BoolExpr* _second;

};


#endif