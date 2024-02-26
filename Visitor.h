#ifndef VISITOR_H
#define VISITOR_H


#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "NumExpr.h"
#include "BoolExpr.h"
#include "Statement.h"
#include "Block.h"
#include "Exceptions.h"
#include "SymbolTable.h"

using namespace std;



class Visitor {
public:
    //NumExpr
    virtual void visitOperator(Operator* opeartor_Node) = 0;
    virtual void visitNumber(Number* nummber_Node) = 0;
    virtual void visitVariable(Variable* variable_Node) = 0;

    //BoolExpr
    virtual int64_t visitRelOp(RelOp* relOp_node) = 0;
    virtual int64_t visitBoolConst(BoolConst* boolConst_Node) = 0;
    virtual int64_t  visitBoolOp(BoolOp* boolOp_Node) = 0;
    
    //Statement
    virtual void visitPrintStmt(PrintStmt* printStmt_Node) = 0;
    virtual void visitSetStmt(SetStmt* setStmt_Node) = 0;
    virtual void visitInputStmt(InputStmt* inputStmt_Node) = 0;
    virtual void visitWhileStmt(WhileStmt* whileStmt_Node) = 0;
    virtual void visitIfStmt(IfStmt* ifStmt_Node) = 0;

    //Block
    virtual void visitBlock(Block* block_Node) = 0;
};


class EvaluationVisitor : public Visitor {
public:
    EvaluationVisitor(): accumulator{}{}

    //NumExpr
    //Per visitare un operator bisogna leggere i due valori e poi metterli insieme in base all'operatore (+,-,*,/)
    void visitOperator(Operator* relOp_Node) override {
        NumExpr* first = relOp_Node->get_first();
        first->accept(this);
        NumExpr* second = relOp_Node->get_second();
        second->accept(this);
        int64_t second_val = accumulator.back(); accumulator.pop_back();
        int64_t first_val = accumulator.back(); accumulator.pop_back();
        switch (relOp_Node->get_op()) {
        case Operator::ADD:
            accumulator.push_back(first_val + second_val); return;
        case Operator::SUB:
            accumulator.push_back(first_val - second_val); return;
        case Operator::MUL:
            accumulator.push_back(first_val * second_val); return;
        case Operator::DIV:
            if (second_val == 0) {
                throw SemanticalError("Divisione per zero");
            }
            else {
                accumulator.push_back(first_val / second_val); return;
            }
        default:
            return;
        }
    }

    void visitNumber(Number* number_Node) override {
        accumulator.push_back(number_Node->get_Value());
    }

    int64_t getValue() const {
        return accumulator.back();
    }

    //visitare una variabile significa controllare che esista e in caso positiva estrarre il valore ad essa associata
    void visitVariable(Variable* variable_Node) override {
        
        accumulator.push_back(symbolTable.search_return(variable_Node->get_Var()));
    }


    //BoolExpr
    //per visitare un RelOp bisogna visitare i due NumExpr e poi combinarli insieme in base all'operatore (<, <, =)
    int64_t visitRelOp(RelOp* relOp_Node) override {
        NumExpr* first = relOp_Node->get_first();
        first->accept(this);
        NumExpr* second = relOp_Node->get_second();
        second->accept(this);
        int64_t second_val = accumulator.back(); accumulator.pop_back();
        int64_t first_val = accumulator.back(); accumulator.pop_back();
        switch (relOp_Node->get_op()) {
        case RelOp::LT:
            return (first_val < second_val);
        case RelOp::GT:
            return (first_val > second_val);
        case RelOp::EQ:
            return (first_val == second_val);
        default:
            return -1;
        }
    }
    //visitare un BoolConst significa vedere se si tratta di TRUE o FALSE e restituire respettivamente 1 o 0
    int64_t visitBoolConst(BoolConst* boolConst_Node) override {
        switch (boolConst_Node->get_lop()) {
        case BoolConst::TRUE: {
            return 1;
        }
        case BoolConst::FALSE: {
            return 0;
        }
        default:
            return -1;
    }
        
    }

    //visitare un BoolOp analizzare i due BoolExpr e poi combinarli insieme in base all'operatore (&&, ||, !)
    int64_t visitBoolOp(BoolOp* boolOp_Node) override {
        switch (boolOp_Node->get_op()) {
        case BoolOp::AND: {
            
            //operatore AND è cortocircuitato
            BoolExpr* first = boolOp_Node->get_first();
            if (!first->accept(this)) {
                return 0;
            }
            BoolExpr* second = boolOp_Node->get_second();
            if (second->accept(this)) {
                return 1;
            }
            else return 0;
        }
    
        //l'operatore OR è cortocircuitato
        case BoolOp::OR: {
            BoolExpr* first = boolOp_Node->get_first();
            if (first->accept(this)) {
                return 1;
            }
            BoolExpr* second = boolOp_Node->get_second();
            if (second->accept(this)) {
                return 1;
            }
            else return 0;
        }
        
        case BoolOp::NOT: {
           
            BoolExpr* first = boolOp_Node->get_first();
            if (first->accept(this)) return 0;
            else return 1;
        }
        default:
            return -1;
        }
    }


    //statemetns
    void visitPrintStmt(PrintStmt* printStmt_Node) override {
        printStmt_Node->get_element()->accept(this);
        cout << getValue() << endl;


        
    }
    void visitSetStmt(SetStmt* setStmt_Node) {

        //cerco nella tabella se esiste la variabile
        //in caso positivo le cambio il suo valore,
        //in caso negativo ne creo una nuova.

        if (symbolTable.search(setStmt_Node->get_first()->get_Var())) {
            setStmt_Node->get_second()->accept(this);
            symbolTable.search_set(setStmt_Node->get_first()->get_Var(), getValue());
        }
        else {
            setStmt_Node->get_second()->accept(this);
            symbolTable.add_var(setStmt_Node->get_first()->get_Var(), getValue());
        }
    }

    void visitInputStmt(InputStmt* inputStmt_Node) {

        //chiedo all'utente di inserie un valore intero da tastiera
        string x;
        do {
            cout << "Inserisce il valore (intero) della variabile " << inputStmt_Node->get_element()->get_Var() << ": ";
            cin >> x;
        } while (!isInt(x));
        stringstream y{};
        y << x;
        int64_t temp;
        y >> temp;

        //dopodichè aggiorno la symbol table
        if (symbolTable.search(inputStmt_Node->get_element()->get_Var())) {
            symbolTable.search_set(inputStmt_Node->get_element()->get_Var(), temp);
        }
        else {
            Variable* temp_var = new Variable(inputStmt_Node->get_element()->get_Var(), temp);
            symbolTable.add_var(temp_var->get_Var(), temp_var->get_value());
        }
    }

    void visitWhileStmt(WhileStmt* whileStmt_Node) {
        while (whileStmt_Node->get_first()->accept(this)) {
            whileStmt_Node->get_second()->accept(this);
        }


    }
    
    void visitIfStmt(IfStmt* ifStmt_Node) {
        if (ifStmt_Node->get_first()->accept(this)) {
            ifStmt_Node->get_second()->accept(this);
        }
        else if (!ifStmt_Node->get_first()->accept(this)) {
            ifStmt_Node->get_third()->accept(this);
        }
    }

    void visitBlock(Block* block_Node) {
        for (int64_t i = 0; i < block_Node->get_statements().size(); i++) {
            block_Node->get_statements()[i]->accept(this);
        }
    }

    bool isInt(string s) {
        if (s == "0") {
            return true;
        }
        else if (s[0] == '-' || (s[0] > '0' && s[0] <= '9')) {
            for (int64_t i = 1; i < s.size(); i++) {
                if (s[i] < '0' || s[i] > '9') {
                    return false;
                }
            }
            return true;
        }
        else return false;

    }


private:
    vector<int64_t> accumulator;
};


#endif
