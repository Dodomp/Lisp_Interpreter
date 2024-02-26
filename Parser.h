#ifndef PARSER_H
#define PARSER_H


#include <vector>
#include <iostream>

#include "Token.h"
#include "BlockManager.h"
#include "StatementManager.h"
#include "NumExprManager.h"
#include "BoolExprManager.h"
#include "Exceptions.h"

using namespace std;

class Parser {
public:
    Parser (BlockManager& bm, StatementManager& sm, NumExprManager& nm, BoolExprManager& bom): block_m{bm}, statement_m{sm}, 
        numexpr_m{nm}, boolexpr_m{bom} {}

    Block* operator () (const vector<Token>& tokenStream) {
        auto tokenItr = tokenStream.begin();
        streamEnd = prev(tokenStream.end());
        Block* block = recursiveBlockParse(tokenItr);
        if (tokenItr == streamEnd) {
            return block;
        }
        else {
            throw ParseError("Errore in fase di Parsing");
        } 
    }

private:

    
    vector<Token>::const_iterator streamEnd;

    //durante la fase di Parsing costruisco anche gli oggetti, che saranno gestiti dai rispettivi manager
    BlockManager& block_m;
    StatementManager& statement_m;
    NumExprManager& numexpr_m;
    BoolExprManager& boolexpr_m;

    //metodi per riconoscere e analizzare le varie parti del testo in input
    Block* recursiveBlockParse(vector<Token>::const_iterator& itr);
    Statement* recursiveStatementParse(vector<Token>::const_iterator& itr);
    NumExpr* recursiveNumExprParse(vector<Token>::const_iterator& itr);
    BoolExpr* recursiveBoolExprParse(vector<Token>::const_iterator& itr);


    //metodo per scorrere l'array di Token in maniera sicura
    void safe_next(std::vector<Token>::const_iterator& itr) {
        if (itr == streamEnd) {
            throw ParseError("Unexpected end of input");
        }
        ++itr;
    }

};



#endif
