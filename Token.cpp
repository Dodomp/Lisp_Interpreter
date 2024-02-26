#include <sstream>

using namespace std;

#include "Token.h"

//metodo per stampare un oggetto Token

ostream& operator<<(ostream& os, const Token& t) {
    std::stringstream tmp;
    tmp << t.tag << " : " << t.word;
    os << tmp.str();
    return os;
}
