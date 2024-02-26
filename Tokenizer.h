#ifndef TOKENIZER_H
#define TOKENIZER_H


using namespace std;
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>



#include "Token.h"








//costruisco la classe TOKANIZER
class Tokenizer {
public:
    vector<Token> operator()(ifstream& inputFile) {
        vector<Token> inputTokens;
        tokenizeInputFile(inputFile, inputTokens);
        return inputTokens;
    }
private:
    void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens);

};

#endif
