#include <stdlib.h>
#include "stackvec.h"

/** TODO: Implementation eines stackbasierten Vektors für `StackData`-Elemente. */

StackVec stackVecNew(StackData storage[], unsigned int size) {
	return (StackVec) {
		.len = 0,
		.size = size,
		.arr = storage       // Persist (on stack) since it comes from main() scope
	};
}

int stackVecPush(StackVec *self, StackData e) {
	if (self->len == self->size){
		return 1;
	}

	self->len = self->len + 1;
	(self->arr)[self->len] = e;
	return 0;
}

StackData* stackVecPop(StackVec *self) {
	if (self->len == 0){
		return NULL;
	}

	int* last_el = &(self->arr)[self->len];
	self->len = self->len - 1;

	return last_el;
}

unsigned int stackVecCapacity(const StackVec *self) {
	return self->size;
}

unsigned int stackVecLen(const StackVec *self) {
	return self->len;
}

int stackVecIsEmpty(const StackVec *self) {
	return self->len == 0;
}

StackData* stackVecPtr(const StackVec *self) {
	return self->arr;
}
