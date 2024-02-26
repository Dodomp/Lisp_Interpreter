
#include <vector>

#include "BoolExpr.h"
#include "Visitor.h"


int64_t RelOp::accept(Visitor* v) {
    return v->visitRelOp(this);
}

int64_t BoolConst::accept(Visitor* v) {
    return v->visitBoolConst(this);
}

int64_t BoolOp::accept(Visitor* v) {
    // TODO: fare con la variabile
    return v->visitBoolOp(this);
}