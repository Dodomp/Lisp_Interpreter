#ifndef NUMEXPR_H
#define NUMEXPR_H

#include <string>


using namespace std;

//la classe visitor è implementata da un'altra parte
class Visitor;


//la classe NumExpr è costituita da 3 sottoclassi
//creo la classe virtuale genitore e poi le tre classi figli che erediteranno dal genitore

//classe virutale genitore
class NumExpr {
public:
    virtual ~NumExpr() {};

    //metodo astratto per al visita dell'albero
    virtual void accept(Visitor* v) = 0;
};

//I classe figlio
class Number : public NumExpr {
public:
    Number(int64_t v) : _value{ v } {};
    ~Number() = default;
    Number(const Number& other) = default;
    Number& operator=(const Number& other) = default;

    int64_t get_Value()const {
        return _value;
    }

    //metodo concreto per al visita dell'albero
    void accept(Visitor* v) override;

private:
    //un Number di fatto è un numero intero sia positivo che negativo
    int64_t _value;
};


//II classe figlio
class Variable : public NumExpr {
public:
    Variable(string v, int64_t value) :_var{ v }, _value { value } {}
    ~Variable() = default;
    Variable(const Variable& other) = default;
    Variable& operator=(const Variable& other) = default;

    string get_Var()const {
        return _var;
    }
    int64_t get_value()const {
        return _value;
    }
    void set_value(int64_t value) { _value = value; }

    //metodo concreto per al visita dell'albero
    void accept(Visitor* v) override; 

private:
    
    //Una Variable è una viariabile  cui è associato un preciso valore
    string _var;
    int64_t _value;
};

//III classe figlio
class Operator : public NumExpr {
public:
    enum OpCode_Operator{ADD, SUB, MUL, DIV};

    Operator(OpCode_Operator op, NumExpr* first, NumExpr* second) : _op{ op }, _first{ first }, _second{ second } {}
    ~Operator() = default;
    Operator(const Operator& other) = default;
    Operator& operator=(const Operator& other) = default;

    OpCode_Operator get_op() const {
        return _op;
    }
    NumExpr* get_first()const {
        return _first;
    }
    NumExpr* get_second()const {
        return _second;
    }
    static OpCode_Operator stringToOpCode_Operator(string s) {
        if (s == "ADD")		 return ADD;
        else if (s == "SUB") return SUB;
        else if (s == "MUL") return MUL;
        else if (s == "DIV") return DIV;
    }

    static string OpCode_OperatorToString(OpCode_Operator op) {
        switch (op) {
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        }
    }

    //metodo concreto per al visita dell'albero
    void accept(Visitor* v) override;

private:

    //un Operator è costituito da un operatore e due NumExpr
    NumExpr* _first;
    NumExpr* _second;
    OpCode_Operator _op;
};


#endif
