#ifndef TOKEN_H
#define TOKEN_H

using namespace std;




#include <sstream>
#include <cstring>
#include <iostream>
#include <stdio.h>


//costruisco la classe TOKEN
struct Token {


    static constexpr int LP = 0;
    static constexpr int RP = 1;
    static constexpr int NUMERO = 2;
    static constexpr int BLOCK = 3;
    static constexpr int INPUT = 4;
    static constexpr int PRINT = 5;
    static constexpr int SET = 6;
    static constexpr int WHILE = 7;
    static constexpr int IF = 8;
    static constexpr int GT = 9;
    static constexpr int LT = 10;
    static constexpr int EQ = 11;
    static constexpr int AND = 12;
    static constexpr int OR = 13;
    static constexpr int NOT = 14;
    static constexpr int TRUE = 15;
    static constexpr int FALSE = 16;
    static constexpr int ADD = 17;
    static constexpr int SUB = 18;
    static constexpr int MUL = 19;
    static constexpr int DIV = 20;
    static constexpr int VARIABILE = 21;
    static constexpr const char* id2word[]{
        "(", ")", "NUMERO", "BLOCK", "INPUT", "PRINT", "SET", "WHILE",
        "IF", "GT", "LT", "EQ", "AND", "OR", "NOT", "TRUE", "FALSE",
        "ADD", "SUB", "MUL", "DIV"
    };
    Token(int64_t t, const char* w) : tag{ t }, word{ w } { }
    Token(int64_t t, string w) : tag{ t }, word{ w } { }

    // La coppia (tag, parola) che costituisce il Token
    int64_t tag;
    string word;

};

ostream& operator<<(std::ostream& os, const Token& t);


#endif
