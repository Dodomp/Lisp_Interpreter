
#include <vector>

#include "Parser.h"
#include "BlockManager.h"
#include "Exceptions.h"

using namespace std;



Block* Parser::recursiveBlockParse(vector<Token>::const_iterator& itr) {
    if (itr->tag == Token::LP) {
        safe_next(itr);
        if (itr->tag == Token::BLOCK) {
            safe_next(itr);
            vector<Statement*> temp;
            temp.push_back(recursiveStatementParse(itr));
            Block* block = new Block(temp);
            safe_next(itr);
            while (itr->tag != Token::RP) {
                block->add_statements(recursiveStatementParse(itr));
                safe_next(itr);
            }
            return block_m.makeBlock(*block);
        }
        else {
            --itr;
            vector<Statement*> temp;
            temp.push_back(recursiveStatementParse(itr));
            Block* block = new Block(temp);
            return block_m.makeBlock(*block);
        }
    }
    else {
        throw ParseError("Unrecognized operator BLOCK");
    }
}

Statement* Parser::recursiveStatementParse(vector<Token>::const_iterator& itr) {
    
    if (itr->tag == Token::LP) {
        safe_next(itr);
        if (itr->tag == Token::INPUT) { //input
            safe_next(itr);
            if (itr->tag == Token::VARIABILE) {
                stringstream temp{};
                temp << itr->word;
                string var;
                temp >> var;
                Variable* variable = new Variable(var, 0);
                safe_next(itr);
                if (itr->tag == Token::RP) {
                    return statement_m.makeInputStmt(variable); 
                }
                else {
                    throw ParseError("Mismatched parenthesis");
                }
            }
            else {
                throw ParseError("Unxepected token");
            }
        }
        else if (itr->tag == Token::PRINT) { 
            safe_next(itr);
            NumExpr* num_expr = recursiveNumExprParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return statement_m.makePrintStmt(num_expr); 
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }
        }
        else if (itr->tag == Token::SET) { 
            safe_next(itr);
            if (itr->tag == Token::VARIABILE) {
                stringstream temp{};
                temp << itr->word;
                string var;
                temp >> var;
                Variable* variable = new Variable(var, 0);
                safe_next(itr);
                NumExpr* num_expr = recursiveNumExprParse(itr);
                safe_next(itr);
                if (itr->tag == Token::RP) {
                    return statement_m.makeSetStmt(variable, num_expr);
                }
                else {
                    throw ParseError("Mismatched parenthesis");
                }
            }
            else {
                throw ParseError("Unxepcted Token");
            }

        }
        else if (itr->tag == Token::WHILE) { 
            safe_next(itr);
            BoolExpr* first = recursiveBoolExprParse(itr);
            safe_next(itr);
            Block* second = recursiveBlockParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return statement_m.makeWhileStmt(first, second);
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }

        }
        else if (itr->tag == Token::IF) { 
            safe_next(itr);
            BoolExpr* first = recursiveBoolExprParse(itr);
            safe_next(itr);
            Block* second = recursiveBlockParse(itr);
            safe_next(itr);
            Block* third = recursiveBlockParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return statement_m.makeIfStmt(first, second, third);
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }
        }
        else {
            throw ParseError("Unexpected token");
        }
    }
    else {
        throw ParseError("Unexpected token");
    }
}

NumExpr* Parser::recursiveNumExprParse(vector<Token>::const_iterator& itr) {
    if (itr->tag == Token::LP) {
        safe_next(itr);
        if (itr->tag >= 17 && itr->tag <= 20) {
            string temp = itr->word;
            safe_next(itr);
            NumExpr* first = recursiveNumExprParse(itr);            
            safe_next(itr);
            NumExpr* second = recursiveNumExprParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return numexpr_m.makeOperator(Operator::stringToOpCode_Operator(temp), first, second);
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }
        }
        else {
            throw ParseError("Unexpected token");
        }
    }
    else if (itr->tag == Token::NUMERO) {
        stringstream temp{};
        temp << itr->word;
        int64_t value;
        temp >> value;
        NumExpr* number = numexpr_m.makeNumber(value);
        return number;
    }
    else if (itr->tag == Token::VARIABILE) {
        std::stringstream temp{};
        temp << itr->word;
        string var;
        temp >> var;
        return numexpr_m.makeVariable(var, 0);
    }
    else {
        throw ParseError("Unexpected token");
        return nullptr;
    }
}

BoolExpr* Parser::recursiveBoolExprParse(vector<Token>::const_iterator& itr) {
    if (itr->tag == Token::LP) {
        safe_next(itr);
        if (itr->tag == Token::LT || itr->tag == Token::GT || itr->tag == Token::EQ) { //lt, gt, eq
            string temp = itr->word;
            safe_next(itr);
            NumExpr* first = recursiveNumExprParse(itr);
            safe_next(itr);
            NumExpr* second = recursiveNumExprParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return boolexpr_m.makeRelOp(RelOp::stringToOpCode_Operator(temp), first, second);
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }

        }
        else if (itr->tag == 12 || itr->tag == 13) { //and, or
            string temp = itr->word;
            safe_next(itr);
            BoolExpr* first = recursiveBoolExprParse(itr);
            safe_next(itr);
            BoolExpr* second = recursiveBoolExprParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return boolexpr_m.makeBoolOp(BoolOp::stringToOpCode_Operator(temp), first, second);
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }
        }
        else if (itr->tag == 14) { //not
            string temp = itr->word;
            safe_next(itr);
            BoolExpr* first = recursiveBoolExprParse(itr);
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return boolexpr_m.makeBoolOp(BoolOp::stringToOpCode_Operator(temp), first, nullptr);
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }
        }
        else if (itr->tag == 15 || itr->tag == 16) { //true, false
            string temp = itr->word;
            safe_next(itr);
            if (itr->tag == Token::RP) {
                return boolexpr_m.makeBoolConst(BoolConst::stringToOpCode_Operator(temp));
            }
            else {
                throw ParseError("Mismatched parenthesis");
            }
        }
        else {
            throw ParseError("Unexpected token");
        }
    }
}