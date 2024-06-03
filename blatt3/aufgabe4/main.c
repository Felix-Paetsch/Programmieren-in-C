#include <stdio.h>
#include "expr.h"

int neg(const Expr *x)                { return -exprEval(x); }
int add(const Expr *x, const Expr *y) { return exprEval(x) + exprEval(y); }
int mul(const Expr *x, const Expr *y) { return exprEval(x) * exprEval(y); }
int div(const Expr *x, const Expr *y) { return exprEval(x) / exprEval(y); }

int main() {
	Expr num[5];
	Expr summed, divided, multiplied, negated;
	
	// Ausdruck: -((3 + 1) * (4 / 2)) == -8
	for (int i = 0; i < 5; ++i)
		exprSetNum(&num[i], i);
	
	exprSetBinary(&summed, &add, &num[3], &num[1]);
	exprSetBinary(&divided, &div, &num[4], &num[2]);
	exprSetBinary(&multiplied, &mul, &summed, &divided);
	
	exprSetUnary(&negated, &neg, &multiplied);
	printf("%i\n", exprEval(&negated));
	
	return 0;
}
