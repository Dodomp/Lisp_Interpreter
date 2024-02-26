#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "Statement.h"
#include "Block.h"

using namespace std;

//classi implementate da un altra parte
class Statement;
class Visitor;

class Block {
public:
    Block(vector<Statement*> statement) : _statements{ statement } {}
    ~Block() = default;
    Block(const Block& other) = default;
    Block& operator=(const Block& other) = default;

    vector<Statement*> get_statements() const {
        return _statements;
    }

    void add_statements(Statement* stmt) {
        _statements.push_back(stmt);
    }

    //metodo per effetaure la visita dell'albero
    void accept(Visitor* v);
private:

    //il Block è un insieme di statement
    vector<Statement*> _statements;
};

#endif