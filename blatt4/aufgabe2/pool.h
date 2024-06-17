/***************************************************************************//**
 * @file pool.h
 * @brief Definitionen für einen Memory-Pool.
 * 
 * Diese Header-Datei enthält Strukturdefinitionen und Funktionsdeklarationen
 * für die Arbeit mit einem Memory-Pool.
 * 
 * ## Anwendungsbeispiel
 * 
 * ```c
 * #include <stdio.h>
 * #include "pool.h"
 * 
 * THUNK(custom_drop, const char *msg) {
 *     printf("%s\n", msg);
 * }
 * 
 * int main(void) {
 *     Pool pool = poolNew();
 *     
 *     SCOPE(&pool) {
 *         poolRegister(&pool, "outer scope", &custom_drop);
 *         
 *         SCOPE(&pool) {
 *             poolRegister(&pool, "inner scope", &custom_drop);
 *         }
 *     }
 *     
 *     poolDrop(&pool);
 *     return 0;
 * }
 * ```
 ******************************************************************************/

#ifndef POOL_H_INCLUDED
#define POOL_H_INCLUDED

#include <stdlib.h>

/**
 * Typedef für eine generische Funktion, die ein Objekt freigibt.
 *
 * @param obj Ein Zeiger auf das freizugebende Objekt.
 */
typedef void (*Drop)(void *obj);

/**
 * Paar aus Objektzeiger und Freigaberoutine.
 */
typedef struct PoolEntry {
	/** @brief Zeiger auf das Objekt. */
    void *obj;
	/** @brief Zeiger auf die Funktion zur Freigabe. */
    Drop drop;
} PoolEntry;

/**
 * Struktur, die den Memory-Pool darstellt.
 */
typedef struct Pool {
	/** @brief Ein dynamisch-wachsendes Array von `PoolEntry`-Instanzen. */
    PoolEntry *resources;
	
	/** @brief Die maximale Kapazität, bevor das Array vergrößert werden muss. */
    size_t capacity;
	
	/** @brief Die aktuelle Anzahl von Elementen im Pool. */
    size_t length;
} Pool;

/**
 * Makro, das einen Scope für den Memory-Pool erstellt.
 *
 * @tparam POOL Der zu verwendende Memory-Pool.
 */
#define SCOPE(POOL) \
	for (int _c = 1; _c != 0; poolPop(POOL), _c = 0) \
		for (poolPush(POOL); _c != 0; _c = 0)

/**
 * @brief Makro, das einen Wrapper um eine Funktion erstellt.
 * 
 * Dieses Makro kann benutzt werden, um eine Destruktorfunktion für einen
 * spezifischen Datentyp in eine Destruktorfunktion mit `void`-Zeiger
 * umzuwandeln. Das ist notwendig, da der C-Standard nicht garantiert, dass
 * Funktionszeigertypen miteinander kompatibel sind, wenn sich die konkreten
 * Parametertypen unterscheiden. Insbesondere ist ein Zeiger auf
 * `void foo(int*)` nicht kompatibel mit einem Zeiger auf `void bar(void*)`.
 * 
 * @tparam NAME Der Name der Funktion.
 * @tparam DECL Die Deklaration des eigentlichen Datentyps.
 */
#define THUNK(NAME, DECL) \
    static inline void NAME ## _helper(DECL); \
    void NAME(void *self) { NAME ## _helper(self); } \
    void NAME ## _helper(DECL)

/**
 * Erstellt einen neuen Memory-Pool.
 */
extern Pool poolNew(void);

/**
 * Gibt alle Ressourcen im Pool frei und zerstört den Pool.
 * 
 * @param self Ein Zeiger auf den Pool.
 */
extern void poolDrop(Pool *self);

/**
 * Schiebt einen neuen Scope auf den Pool.
 * 
 * @param self Ein Zeiger auf den Pool.
 */
extern void poolPush(Pool *self);

/**
 * Poppt den aktuellen Scope vom Pool und gibt alle in diesem Scope
 * registrierten Ressourcen frei.
 * 
 * @param self Ein Zeiger auf den Pool.
 */
extern void poolPop(Pool *self);

/**
 * Registriert ein Objekt im aktuellen Scope des Pools.
 *
 * @param self Ein Zeiger auf den Pool.
 * @param obj  Ein Zeiger auf das zu registrierende Objekt.
 * @param drop Eine Funktion, die das Objekt freigibt.
 */
extern void poolRegister(Pool *self, void *obj, Drop drop);

#endif
