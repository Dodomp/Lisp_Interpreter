#include "Block.h"
#include "Visitor.h"

using namespace std;

void Block::accept(Visitor* v) {
    v->visitBlock(this);
}