#include <stdio.h>
#include <assert.h>

#include "stackvec.h"

int main() {
	int storage[1024];
	StackVec vec = stackVecNew(storage, sizeof(storage)/sizeof(*storage));
	
	for (int i = 0; i < 10; ++i)
		assert(stackVecPush(&vec, i*i) == 0);
	
	for (int *i = stackVecPtr(&vec), *end = i + stackVecLen(&vec); i < end; ++i)
		printf("%i\n", *i);
	
	int *last_element = stackVecPop(&vec);
	assert(last_element != NULL);
	assert(*last_element == 9 * 9);
	
	return 0;
}
