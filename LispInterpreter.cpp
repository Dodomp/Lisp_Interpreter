#include <iostream>
#include <fstream>
#include <vector>


#include "Token.h"
#include "Tokenizer.h"
#include "Exceptions.h"
#include "BlockManager.h"
#include "StatementManager.h"
#include "NumExprManager.h"
#include "BoolExprManager.h"
#include "Exceptions.h"
#include "Parser.h"
#include "Visitor.h"
#include "SymbolTable.h"

//#define DEBUG_MODE
//#define PRE_PRODUCTION
//#define POST_PRODUCTION 
using namespace std;






int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << "File non specificato" << endl;
        cerr << "Utilizzare: " << argv[0] << " <nome_file>" << endl;
        return EXIT_FAILURE;
    }

        /*** APERTURA FILE ***/
        ifstream inputFile;
        try {
            inputFile.open(argv[1]);
        }
        catch (std::exception& exc) {
            cerr << "Non posso aprire " << argv[1] << std::endl;
            cerr << exc.what() << std::endl;
            return EXIT_FAILURE;
        }

       

        /*** FASE DI TOKENIZZAZIONE ***/
        Tokenizer tokenize;
        std::vector<Token> inputTokens;

        try {
            inputTokens = tokenize((inputFile));
            inputFile.close();
        }
        catch (LexicalError& le) {
            cerr << "Errore in fase di analisi lessicale" << std::endl;
            cerr << le.what() << std::endl;
            return EXIT_FAILURE;
        }
        catch (SintaxError& se) {
            cerr << "Errore sintattico" << std::endl;
            cerr << se.what() << std::endl;
            return EXIT_FAILURE;
        }
        catch (std::exception& exc) {
            cerr << "Non posso leggere da " << argv[1] << std::endl;
            cerr << exc.what() << std::endl;
            return EXIT_FAILURE;
        }


        //creto i Manager necessari per il Parser
        BlockManager BLManager;
        StatementManager STManager;
        NumExprManager NEManager;
        BoolExprManager BEManager;

        //// Creo il function object per il parsing
        Parser parser(BLManager, STManager, NEManager, BEManager);

        //*** FASE DI PARSING ***//
        try {
            Block* block = parser(inputTokens);
                      
            //cout << std::endl;

            EvaluationVisitor* v = new EvaluationVisitor();
            //cout << "Console outoput: " << endl;
            block->accept(v);


        }
        catch (SemanticalError& exc) {
            cerr << "ERROR in fase di Evaluation" << endl;
            cerr << exc.what() << endl;
            return EXIT_FAILURE;
        }
        catch (exception& exc) {
            cerr << "ERROR in fase di Parsing" << endl;
            cerr << exc.what() << endl;
            return EXIT_FAILURE;
        }


        return EXIT_SUCCESS;


}


