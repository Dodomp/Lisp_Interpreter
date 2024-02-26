#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H


#include <vector>
#include <iostream>

#include "NumExpr.h"
#include "Exceptions.h"

using namespace std;


//SymbolTable è una classe globale che svolge una funzione di contenitore delle variabili
//che vengono dichiarate durante l'esecuzione del programma
class SymbolTable {
public:
    SymbolTable() = default;

    vector<Variable*> get_st() const {
        return _st;
    }
    //metodo per aggiungere un variabile
    void add_var(string s, int64_t value) {
        Variable* var = new Variable(s, value);
        _st.push_back(var);
    }
    //metodo per cercare una viaribile e restituisce il valore
    int64_t search_return(string s) {
        for (int i = 0; i < _st.size(); i++) {
            if (_st[i]->get_Var() == s) {
                return _st[i]->get_value();
            }
        }
        throw SemanticalError("Variable not found");
    }

    //metodo per verificare se una variabile è già presente o meno
    int64_t search(string s) {
        for (int i = 0; i < _st.size(); i++) {
            if (_st[i]->get_Var() == s) {
                return 1;
            }
        }
        return 0;
    }

    //metodo per cercare una variabile e modificarle il valore
    void search_set (string s, int64_t v) {
        for (int i = 0; i < _st.size(); i++) {
            if (_st[i]->get_Var() == s) {
                _st[i]->set_value(v);
            }
        }
    }


private:
    vector<Variable*> _st;
};


extern SymbolTable symbolTable;


#endif
