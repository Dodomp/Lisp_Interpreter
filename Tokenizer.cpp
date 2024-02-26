#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#include "Tokenizer.h"
#include "Exceptions.h"

#define DEBUG

void Tokenizer::tokenizeInputFile(std::ifstream& inputFile,
    std::vector<Token>& inputTokens) {

    char ch;
    ch = inputFile.get();


    //controllo che il file non sia vuoto
    if (inputFile.peek() == ifstream::traits_type::eof()) {
        throw SintaxError(" ERROR Empty file");
    }
    else {
        while (!inputFile.eof()) {
            if (std::isspace(ch)) {
                // Salto lo "spazio bianco"
                ch = inputFile.get();
                continue;
            }

            if (ch == '(') {
                inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP] });
            }
            else if (ch == ')') {
                inputTokens.push_back(Token{ Token::RP, Token::id2word[Token::RP] });
            }
            else if (ch == '-') {
                std::stringstream tmp{};
                tmp << ch;
                do {
                    ch = inputFile.get();
                    if (std::isdigit(ch))
                        tmp << ch;
                    else if (ch == ' ' || ch == '(' || ch == ')') {
                        continue;
                    }
                    else {
                        std::stringstream tmp{};
                        tmp << "ERROR lessicale sul simbolo: " << ch;
                        throw LexicalError(tmp.str());
                    }
                } while (std::isdigit(ch));
                inputTokens.push_back(Token{ Token::NUMERO, tmp.str() });
                continue;
            }
            else if (std::isdigit(ch)) {
                // Costante intera
                std::stringstream tmp{};
                tmp << ch;
                do {
                    ch = inputFile.get();
                    if (std::isdigit(ch)) tmp << ch;
                    else if (ch != ' ' && ch != ')' && ch != '\n') {
                        std::stringstream tmp{};
                        tmp << "ERROR lessicale sul simbolo: " << ch;
                        throw LexicalError(tmp.str());
                    }
                } while (std::isdigit(ch));
                inputTokens.push_back(Token{ Token::NUMERO, tmp.str() });
                continue;
            }
            else if (std::isalpha(ch)) {
                // Costante intera
                std::stringstream tmp{};
                tmp << ch;
                do {
                    ch = inputFile.get();
                    if (std::isalpha(ch)) tmp << ch;
                    else if (ch != ' ' && ch != '\n' && ch != ')') {
                        std::stringstream tmp{};
                        tmp << "ERROR lessicale sul simbolo: " << ch;
                        throw LexicalError(tmp.str());
                    }
                } while (std::isalpha(ch));

                std::string to_compare = "" + tmp.str();

                bool trovata = false;
                for (const std::string& elemento : Token::id2word) {
                    if (elemento == to_compare) {
                        trovata = true;
                        break;
                    }
                }
                if (trovata) {
                    if (to_compare == Token::id2word[Token::BLOCK])
                        inputTokens.push_back(Token{ Token::BLOCK, to_compare });
                    else if (to_compare == Token::id2word[Token::INPUT])
                        inputTokens.push_back(Token{ Token::INPUT, to_compare });
                    else if (to_compare == Token::id2word[Token::PRINT])
                        inputTokens.push_back(Token{ Token::PRINT, to_compare });
                    else if (to_compare == Token::id2word[Token::SET])
                        inputTokens.push_back(Token{ Token::SET, to_compare });
                    else if (to_compare == Token::id2word[Token::WHILE])
                        inputTokens.push_back(Token{ Token::WHILE, to_compare });
                    else if (to_compare == Token::id2word[Token::IF])
                        inputTokens.push_back(Token{ Token::IF, to_compare });
                    else if (to_compare == Token::id2word[Token::GT])
                        inputTokens.push_back(Token{ Token::GT, to_compare });
                    else if (to_compare == Token::id2word[Token::LT])
                        inputTokens.push_back(Token{ Token::LT, to_compare });
                    else if (to_compare == Token::id2word[Token::EQ])
                        inputTokens.push_back(Token{ Token::EQ, to_compare });
                    else if (to_compare == Token::id2word[Token::AND])
                        inputTokens.push_back(Token{ Token::AND, to_compare });
                    else if (to_compare == Token::id2word[Token::OR])
                        inputTokens.push_back(Token{ Token::OR, to_compare });
                    else if (to_compare == Token::id2word[Token::NOT])
                        inputTokens.push_back(Token{ Token::NOT, to_compare });
                    else if (to_compare == Token::id2word[Token::TRUE])
                        inputTokens.push_back(Token{ Token::TRUE, to_compare });
                    else if (to_compare == Token::id2word[Token::FALSE])
                        inputTokens.push_back(Token{ Token::FALSE, to_compare });
                    else if (to_compare == Token::id2word[Token::ADD])
                        inputTokens.push_back(Token{ Token::ADD, to_compare });
                    else if (to_compare == Token::id2word[Token::SUB])
                        inputTokens.push_back(Token{ Token::SUB, to_compare });
                    else if (to_compare == Token::id2word[Token::MUL])
                        inputTokens.push_back(Token{ Token::MUL, to_compare });
                    else if (to_compare == Token::id2word[Token::DIV])
                        inputTokens.push_back(Token{ Token::DIV, to_compare });
                }
                else {
                    inputTokens.push_back(Token{ Token::VARIABILE, tmp.str() });
                }

                continue;
            }
            else {
                // Ci sono dei simboli non riconosciuti dal tokenizzatore nel file
                // Utilizzo il meccanismo delle eccezioni per segnalare l'errore lessicale
                std::stringstream tmp{};
                tmp << "ERROR lessicale sul simbolo: " << ch;
                throw LexicalError(tmp.str());
            }
            ch = inputFile.get();
        }
    }    
}