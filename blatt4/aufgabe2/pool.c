/***************************************************************************//**
 * @file pool.c
 * @brief Implementation des Memory-Pools.
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "pool.h"

/* *** interne Hilfsfunktionen ********************************************** */

static PoolEntry* grow(PoolEntry *array, size_t new_cap) {
    PoolEntry *new_array = realloc(array, new_cap * sizeof(PoolEntry));
    if (new_array == NULL) {
        fprintf(stderr, "Failed to allocate memory for resizing array\n");
        exit(-1);
    }
    return new_array;
}

/* *** öffentliche Schnittstelle ******************************************** */

Pool poolNew(void) {
	Pool p = {
		.length = 0,
		.capacity = 2,
		.resources = malloc(2 * sizeof(PoolEntry))
	};

	if (p.resources == NULL) {
        fprintf(stderr, "Failed to allocate initial memory for pool\n");
        exit(-1);
    }

	return p;
}

void poolDrop(Pool *self) {
	for (int i = self->length - 1; i >= 0; i--){
		PoolEntry entry = self->resources[i];

		if (entry.obj != NULL){
			entry.drop(entry.obj);
		} else {
			entry.drop(entry.obj);
		}
	}

	free(self->resources);
	self->length = 0;
	self->capacity = 0;
}

void poolPush(Pool *self) {
	// NULL represents the boundary between scopes
	poolRegister(self, NULL, NULL);
}

void poolPop(Pool *self) {
	for (int i = self->length - 1; i >= 0; i--){
		PoolEntry entry = self->resources[i];
		self->length --;
		if (entry.obj != NULL){
			entry.drop(entry.obj);
		} else {
			return;
		}
	}
}

void poolRegister(Pool *self, void *obj, Drop drop) {
	if (self->capacity < self->length + 1){
		self->capacity = (self->capacity * 3 + 1)/2;
		self->resources = grow(self->resources, self->capacity);
	}

	self->resources[self->length] = (PoolEntry) {
		.obj = obj,
		.drop = drop
	};

	self->length = self->length + 1;
}
