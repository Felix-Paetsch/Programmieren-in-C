## Aufgabe 1

### Kompatibilität von Funktionszeigertypen

### Duff's Device

## Aufgabe 2

### Funktionsweise des `THUNK`-Makros
Das Makro ersetzt

```C
    THUNK(poolDestruktor, Pool* pool){ ... }
```

durch 

```C
    static inline void poolDestruktor_helper(Pool* pool);
    void poolDestruktor(void *self) { poolDestruktor_helper(self); }
    void poolDestruktor_helper(Pool* pool){ ... }
```

es erstellt die neue Funktion `poolDestruktor` - das erste Argument von `THUNK`, welche einen void Pointer nimmt und damit den Funktionskörper aufruft, der nach THUNK() spezifiziert ist.
Beim Aufruf von poolDestruktor() wird ein Pool pointer zu einem Void pointer gecastet und dieser dann wieder zu einem Pool pointer.

Das wird benötigt, da Pointer verschiedener Typen zwar zum Void pointer kompatiebel sind, aber nicht direkt zueinander. Die Funktionen, die auf dem Pool arbeiten, insbesondere `poolDrop` und `poolRegister` sollen aber mit Funktionen arbeiten können, die Pointer auf Objekte beliebiger Typen annehmen, brauchen also Void Pointer.


### Funktionsweise des `SCOPE`-Makros
Das Makro Scope ersetzt

```C
    SCOPE(&pool) ...
```

durch

```C
    for (int _c = 1; _c != 0; poolPop(&pool), _c = 0) \
        for (poolPush(&pool); _c != 0; _c = 0)
```

die Initialisierungsbedingung der inneren Schleife `poolPush(&pool)` sorgt dafür, dass vor allen Dingen, die innerhalb des Scopes passieren, ein neuer Scope erstellt wird.
Der Iterationsschritt der ersten Schleife wird am Ende des Scopes (zum ersten/einzigen Mal) ausgeführt und entfernt diesen wieder. Die Variable _c sorgt dafür, dass jede Schleife nur genau einmal ausgeführt wird - sogar unabhängig davon ob _c im Schleifenkörper neu gesetzt wird.

## Aufgabe 3

### Funktionsweise des `vecForEach`-Makros
