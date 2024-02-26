#ifndef STATEMENT_H
#define STATEMENT_H

#include "NumExpr.h"
#include "BoolExpr.h"

//#include "Block.h"

using namespace std;

//calsse Block implementata da un'altra parte
class Block;

//classe visitor implementata da un'altra parte
class Visitor;

// la classe Statement è costituita da cinque sottoclassi
//creo la classe virtuale genitore e poi le cinque classi figli che erediteranno dal genitore

//classe virtuale
class Statement {
public:
    virtual ~Statement() {};
    //metodo virtuale per visitare l'albero
    virtual void accept(Visitor* v) = 0;
};

//I classe figlio
class PrintStmt : public Statement {
public:
    PrintStmt(NumExpr* element) : _element{ element } {};
    ~PrintStmt() = default;
    PrintStmt(const PrintStmt& other) = default;
    PrintStmt& operator=(const PrintStmt& other) = default;

    
    NumExpr* get_element()const {
        return _element;
    }

    void accept(Visitor* v) override;

private:
    NumExpr* _element;
};

//II classe figlio
class SetStmt : public Statement {
public:
    SetStmt(Variable* first, NumExpr* second) :  _first{ first }, _second{ second } {};
    ~SetStmt() = default;
    SetStmt(const SetStmt& other) = default;
    SetStmt& operator=(const SetStmt& other) = default;

    //getters
    Variable* get_first()const {
        return _first;
    }
    NumExpr* get_second()const {
        return _second;
    }
    //setters
    void set_first(Variable* first) {
        _first = first;
    }
    void set_second(NumExpr* second) {
        _second = second;
    }

    //metodo concreto per la visita
    void accept(Visitor* v) override;

private:
    Variable* _first;
    NumExpr* _second;
};

//III classe figlio
class InputStmt : public Statement {
public:
    InputStmt(Variable* element) : _element{ element } {};
    ~InputStmt() = default;
    InputStmt(const InputStmt& other) = default;
    InputStmt& operator=(const InputStmt& other) = default;

    //getter
    Variable* get_element()const {
        return _element;
    }
    
    //metodo concreto per la visita
    void accept(Visitor* v) override;

private:
    Variable* _element;
};

//IV clsse figlio
class WhileStmt : public Statement {
public:
    WhileStmt(BoolExpr* first, Block* second) : _first{ first }, _second{ second } {};
    ~WhileStmt() = default;
    WhileStmt(const WhileStmt& other) = default;
    WhileStmt& operator=(const WhileStmt& other) = default;
    

    //getters
    BoolExpr* get_first()const {
        return _first;
    }
    Block* get_second()const {
        return _second;
    }

    //metodo concreto per la visita
    void accept(Visitor* v) override;


private:
    BoolExpr* _first;
    Block* _second;
};


//V classe figlio
class IfStmt : public Statement {
public:
    IfStmt(BoolExpr* first, Block* second, Block* third) : _first{ first }, _second{ second }, _third{ third } {};
    ~IfStmt() = default;
    IfStmt(const IfStmt& other) = default;
    IfStmt& operator=(const IfStmt& other) = default;

    
    //getters
    BoolExpr* get_first() const {
        return _first;
    }
    Block* get_second() const {
        return _second;
    }
    Block* get_third() const {
        return _third;
    }

    //metodo concreto per la visita
    void accept(Visitor* v) override;

private:
    BoolExpr* _first;
    Block* _second;
    Block* _third;
};




#endif
