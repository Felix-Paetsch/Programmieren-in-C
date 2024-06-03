#ifndef EXPR_H_INCLUDED
#define EXPR_H_INCLUDED

typedef struct Expr Expr;
typedef int (*UnaryFn)(const Expr*);
typedef int (*BinaryFn)(const Expr*, const Expr*);

/**
 * Ein Variantentyp, der entweder eine Integer-Zahl, eine unäre Funktion oder
 * eine binäre Funktion enthält.
 */
struct Expr {
	enum { F_UNARY, F_BINARY, NUM } type;
	union {
		int value;
		struct {
			UnaryFn fun;
			const Expr* arg;
		} data_unary;
		struct {
			BinaryFn fun;
			const Expr* arg1;
			const Expr* arg2;
		} data_binary;
	} term;
};

/**
 * Setzt den Ausdruck auf einen numerischen Wert.
 */
extern void exprSetNum(Expr *self, int d);

/**
 * Setzt den Ausdruck auf eine unäre Funktion mit dem Ausdrucksargument.
 */
extern void exprSetUnary(Expr *self, UnaryFn f, const Expr *x);

/**
 * Setzt den Ausdruck auf eine binäre Funktion mit den Ausdrucksargumenten.
 */
extern void exprSetBinary(Expr *self, BinaryFn f, const Expr *x, const Expr *y);

/**
 * Berechnet den numerischen Wert des Ausdrucks, indem entweder die
 * Integer-Zahl zurückgegeben, oder die unäre bzw. binäre Funktion gerufen wird.
 */
extern int exprEval(const Expr *self);

#endif
