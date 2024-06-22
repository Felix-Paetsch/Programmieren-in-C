## Aufgabe 1

### Kompatibilität von Funktionszeigertypen
```c
void foo(void*);
void bar(int*);

void (*f1)(void*) = &foo; // erlaubt
void (*f2)(void*) = &bar; // Übersetzungsfehler
```
Warum wird dieses Verhalten nicht ohne den expliziten Cast unterstützt, so wie die Umwandlung von int* nach void* auch ohne Cast erlaubt ist?

Die Umwandlung von int* (oder Ähnlichem) zu void* wird meistens benutzt um Dinge zu machen, die nur mit Pointern zu tun haben und weniger mit ihrem Inhalt. (Zum Beispiel sortieren).
Wenn wir implizite Casts wie Vorgeschlagen für Funktionstypen benutzen wollen, dann vergessen wir nur einen Teil der Information des Objekts, zu dem gezeigt wird. Bei diesem Cast wird nicht einfach ein Typ vergessen, sondern ein anderer Typ deklariert.
Dies ist in den meisten Projekten häufiger ein Fehler als intendiertes Verhalten und wird deshalb nicht akzeptiert. 

### Duff's Device
```c
void copy(char *to, const char *from, size_t count) {
    switch (count % 8) {
        do {
            count -= 8;
    case 0: *to++ = *from++;
    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
        } while (count > 8);
    }
}
```

Es werden chars (bytes) von from nach to kopiert. Falls count ein Vielfaches von 8 ist, wird von Count kontinuierlich 8 abgezogen und der erste Fall und alle darauf folgenden werden dabei immer ausgeführt, also die nächsten 8 Bytes kopiert. 
Falls count nicht Vielfaches von 8 ist, andernfalls tritt das switch statement in den Fall ein, dass erst der Rest von count nach division durch 8 kopiert wird und dann count ein Vielfaches von 8 ist und wir uns in derselben Situation wie im ersten Fall befinden.

Die offensichtliche Alternative zu der Funktion ist
```c
void copy(char *to, const char *from, size_t count) {
    while (count-- > 0){
        *to++ = *from++;
    }
}
```

Duffs device führt in einem Schleifendurchlauf mehrere der Schleifendurchläufe der zweiten Variante aus,
worduch beim Programmdurchlauf weniger zwischen Anweisungen gesprungen werden muss.

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

```c
    for (size_t _it = 0, _len = vecLen(vec), _c = 0; (_c ^= 1) && _it < _len; ++_it) \
		for (var = &(vec)[_it]; _c != 0; _c = 0)
```

In der äußeren Schleife wird geht die Variable `_it` die Werte zwischen 0 und der Länge des Vektors - 1 durch, also alle Indices der Vektorelemente. In der inneren Schleife wird der passenden Eintrage des Vektors
auf `var` (eine Variablendeklaration) gesetzt, mit dem dann gearbeitet wird. Die innere Schleife ist notwendig, damit wir am Ende _c wieder zu 0 setzen können, falls es in der Schleife verändert wurde.

Die Variable _c sorgt dafür, dass jede Schleife passend oft ausgeführt wird, selbst wenn _c selber neu in der Schleife benutzt wird.
_len/_it dürfen allerding, um die Funktionalität zu sichern, nicht in der inneren Schleife bearbeitet werden.