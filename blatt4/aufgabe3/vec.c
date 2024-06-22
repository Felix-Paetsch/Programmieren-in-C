/***************************************************************************//**
 * @file vec.c
 * @brief Implementation des generischen Vektortyps.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h to use memcpy

#include "vec.h"

/* Hilfsmakro für die Markierung noch unimplementierter Funktionen */
#define TODO(MSG) do { \
	fprintf(stderr, "TODO: " #MSG "\n"); \
	exit(-1); \
} while (0)

/* *** öffentliche Schnittstelle ******************************************** */

/* (die runden Klammern um einige Funktionsnamen sind notwendig, da Makros
 * gleichen Namens existieren und der Präprozessor diese expandieren würde) */

void vecDrop(void *self) {
	if (self == NULL){
		return;
	}

	VecHeader* header_ptr = (VecHeader*) self - 1;
	free(header_ptr);
}

void* (vecPush)(void *self, size_t size) {
	if (self == NULL){
		size_t alloc_size = sizeof(VecHeader) + size;
		VecHeader* header_ptr  = malloc(alloc_size);
		*header_ptr = (VecHeader) {
			.len = 1,
			.cap = alloc_size
		};
		return header_ptr + 1;
	}
	
	VecHeader* header_ptr = (VecHeader*) self - 1;
	if ((header_ptr->len + 1) * size <= header_ptr->cap - sizeof(VecHeader)){
		header_ptr->len = header_ptr->len + 1;
		return self;
	}

	size_t new_len    = header_ptr->len + 1;
	size_t alloc_size = sizeof(VecHeader) + size*new_len;

	VecHeader* new_header_ptr = (VecHeader*) realloc(header_ptr, alloc_size);
	*new_header_ptr = (VecHeader) {
		.len = new_len,
		.cap = alloc_size
	};
	
	return new_header_ptr + 1;
}

void (vecPop)(void *self) {
	if (vecIsEmpty(self)){
		return;
	}

	VecHeader* header_ptr = (VecHeader*) self - 1;
	header_ptr->len = header_ptr->len - 1;
}

int vecIsEmpty(const void *self) {
	return vecLen(self) == 0;
}

size_t vecLen(const void *self) {
	if (self == NULL){
		return 0;
	}

	const VecHeader* header_ptr = (VecHeader*) self - 1;
	return header_ptr->len;
}
