#ifndef STACKVEC_H_INCLUDED
#define STACKVEC_H_INCLUDED

/**
 * Unterliegender Element-Typ für das Stack-Array.
 */
typedef int StackData;

/**
 * Ein zusammenhängender Vektor-Typ, der mit stackbasiertem Speicher hinterlegt
 * ist.
 */
typedef struct StackVec {
	int size;
	int len;
	int* arr;
} StackVec;

/**
 * Initialisiert einen leeren `StackVec` unter Verwendung von `storage` als
 * Backend-Speicher.
 *
 * Der `StackVec` ist in der Lage `size` viele Werte zu speichern.
 */
extern StackVec stackVecNew(StackData storage[], unsigned int size);

/**
 * Fügt ein neues Element zu diesem Vektor hinzu. Scheitert mit einem
 * Fehlercode, wenn die Kapazität überschritten würde.
 */
extern int stackVecPush(StackVec* self, StackData e);

/**
 * Wenn dieser Vektor nicht leer ist, entfernt er das letzte Element und gibt
 * einen Zeiger darauf zurück. Andernfalls wird `NULL` zurückgegeben.
 */
extern StackData* stackVecPop(StackVec* self);

/**
 * Gibt die Anzahl der Elemente zurück, die dieser Vektor halten kann.
 */
extern unsigned int stackVecCapacity(const StackVec* self);

/**
 * Gibt die Anzahl der Elemente zurück, die derzeit im Vektor gespeichert sind.
 */
extern unsigned int stackVecLen(const StackVec* self);

/**
 * Gibt 1 zurück, wenn der Vektor keine Elemente enthält.
 */
extern int stackVecIsEmpty(const StackVec* self);

/**
 * Gibt einen Zeiger auf das Array zurück, das den gesamten Vektor enthält.
 */
extern StackData* stackVecPtr(const StackVec* self);

#endif
