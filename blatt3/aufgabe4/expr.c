#include "expr.h"

/** TODO: Implementation eines Choice-Typs mit drei möglichen Datentypen. */

void exprSetNum(Expr *self, int d) {
	self->type = NUM;
    self->term.value = d;
}

void exprSetUnary(Expr *self, UnaryFn f, const Expr *x) {
	self->type = F_UNARY;
    self->term.data_unary.fun = f;
    self->term.data_unary.arg = x;
}

void exprSetBinary(Expr *self, BinaryFn f, const Expr *x, const Expr *y) {
	self->type = F_BINARY;
    self->term.data_binary.fun = f;
    self->term.data_binary.arg1 = x;
    self->term.data_binary.arg2 = y;
}

int exprEval(const Expr *self) {
	if (self->type == NUM){
		return self->term.value;
	}

	if (self->type == F_UNARY){
		const Expr* arg = self->term.data_unary.arg;
		UnaryFn fun     = self->term.data_unary.fun;
    	return fun(arg);
	}
	
	const Expr* arg1 = self->term.data_binary.arg1;
	const Expr* arg2 = self->term.data_binary.arg2;
	BinaryFn fun     = self->term.data_binary.fun;
    return fun(arg1, arg2);
}
