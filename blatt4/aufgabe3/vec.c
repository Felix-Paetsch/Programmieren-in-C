/***************************************************************************//**
 * @file vec.c
 * @brief Implementation des generischen Vektortyps.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

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
	TODO("vecDrop implementieren");
}

void* (vecPush)(void *self, size_t size) {
	TODO("vecPush implementieren");
	return NULL;
}

void (vecPop)(void *self) {
	TODO("vecPop implementieren");
}

int vecIsEmpty(const void *self) {
	TODO("vecIsEmpty implementieren");
	return 1;
}

size_t vecLen(const void *self) {
	TODO("vecLen implementieren");
	return 0;
}
