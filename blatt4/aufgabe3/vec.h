/***************************************************************************//**
 * @file vec.h
 * @brief Generischer Vektortyp.
 * 
 * Diese Datei enthält eine Implementierung eines generischen Vektortyps. Um zu
 * bestimmen, welche Art von Elementen dieser Vektor enthält, deklariert man
 * eine Variable, die ein Zeiger auf den Typ der Elemente ist. Dieser Zeiger
 * kann dann initialisiert und verwendet werden, als ob er auf ein Array
 * variabler Länge zeigt.
 * 
 * ## Anwendungsbeispiel
 * 
 * ```c
 * #include <stdio.h>
 * #include "vec.h"
 * 
 * int main(void) {
 *     int *vec = NULL;
 *     
 *     vecPush(vec, 1);
 *     vecPush(vec, 2);
 *     vecPush(vec, 3);
 *     
 *     while (!vecIsEmpty(vec))
 *         printf("%i\n", vecPop(vec));
 *     
 *     vecRelease(vec);
 * }
 * ```
 ******************************************************************************/

#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

/* *** Includes ************************************************************* */

#include <stddef.h>

/* *** Strukturen *********************************************************** */

/**
 * @brief Struktur, die dem Array zur Buchhaltung vorangestellt ist.
 */
typedef struct {
    size_t len; /**< @brief Anzahl der Elemente im Vektor. */
    size_t cap; /**< @brief Kapazität des reservierten Speichers. */
} VecHeader;

/* *** Schnittstelle ******************************************************** */

/**
 * @brief Gibt den Speicher eines Vektors frei.
 * @param self  Der freizugebende Vektor
 */
extern void vecDrop(void *self);

/**
 * @internal
 * @brief Reserviert Platz für einen neuen Wert im Vektor.
 * @param self  Der Vektor
 * @param size  Größe der Vektorelemente
 * @return Der neue Zeiger auf den Anfang des Vektors
 */
extern void* vecPush(void *self, size_t size);

/**
 * Fügt ein Element zum Ende des Vektors hinzu.
 * 
 * Das Makro kann folgendermaßen verwendet werden:
```
    float *myVec = NULL;
    vecPush(myVec, 0.5);
```
 */
#define vecPush(self, ...) \
    self = vecPush(self, sizeof(__VA_ARGS__)), self[vecLen(self) - 1] = __VA_ARGS__

/**
 * @internal
 * @brief Löscht das letzte Element des Vektors.
 * @param self  Der Vektor
 */
extern void vecPop(void *self);

/**
 * Entfernt ein Element vom Ende des Vektors und gibt eine lvalue-Referenz
 * zurück.
 * 
 * Das Makro kann folgendermaßen verwendet werden:
```
    float *myVec = NULL;
    float x;

    vecPush(myVec) = 0.5;
    vecPush(myVec) = 1.5;
    vecPush(myVec) = 2.5;

    x = vecPop(myVec); // ergibt 2.5
```
 */
#define vecPop(self) \
    *(self + vecLen(self) - 1), (vecPop)(self)

/**
 * @brief Gibt das letzte Element des Vektors zurück.
 * @param self  Der Vektor
 * @return Referenz auf das oberste Element von \p self
 */
#define vecTop(self) \
    self + vecLen(self) - 1

/**
 * Durchläuft jedes Element des Vektors in Reihenfolge.
 * 
 * Das Makro kann folgendermaßen verwendet werden:
```
    float *myVec = NULL;

    vecPush(myVec) = 0.5;
    vecPush(myVec) = 1.5;
    vecPush(myVec) = 2.5;

    vecForEach(float *x, myVec) {
        // mache etwas mit x
    }
```
 */
#define vecForEach(var, vec) \
	for (size_t _it = 0, _len = vecLen(vec), _c = 0; (_c ^= 1) && _it < _len; ++_it) \
		for (var = &(vec)[_it]; _c != 0; _c = 0)

/**
 * @brief Gibt zurück, ob der Vektor leer ist.
 * @param self  Der Vektor
 * @return 0, wenn nicht leer\n
 *      != 0, wenn leer
 */
extern int vecIsEmpty(const void *self);

/**
 * @brief Gibt die Anzahl der im Vektor verwendeten Elemente zurück.
 * @param self  Der Vektor
 * @return Anzahl der Elemente in \p self
 */
extern size_t vecLen(const void *self);

#define DEFINE_VAR(TYPE, VAR) TYPE *VAR = NULL


#endif /* VEC_H_INCLUDED */
