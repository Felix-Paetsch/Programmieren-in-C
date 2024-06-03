#include <stdlib.h>

// TODO: diese Deklaration leserlich machen

struct S;
// void (*(*const dispatch[10])(const char*))(int, int (*)(struct S*));

typedef int ArgumentFunction(struct S*);
typedef void InnerFunction(int, ArgumentFunction*);
typedef InnerFunction* OuterFunction(const char*);

OuterFunction* const dispatch[10];

int main() {
	if (dispatch[0])
		dispatch[0]("1")(2, NULL);
}
