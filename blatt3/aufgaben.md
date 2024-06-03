## Aufgabe 1

### Datenlayout von Strukturen
Union hat die Größe des maximalen Elements, also

    max(size_t(int), size_t(float)) = size_t(float)

Das Padding ist abhänging von der Größe des größten Elements, also

    max(size_t(float), size_t(char)) = size_t(float)
    max(size_t(float), size_t(int))  = size_t(float)

In beiden Fällen passt tag in die ersten size_t(float) bytes
und die Union dann in die zweiten size_t(float) bytes,
also ist die Größe der beiden Strukturen gleich.


### Typalias und Strukturtyp
Namen an Strukturen helfen bei der Übersichtlichkeit für die Programmierer
zudem erlauben sie beim Compilieren zusätzliche (logische) Fehler zu finden.

Darüber hinaus ermöglichen sie rekursive Typendefinition für zB Bäume, was sonst nicht ginge.
Zudem gibt es bei Funktionssignaturen Probleme, da sie genau dieselben Typen referenzieren müssen.

### Enumerationswerte

const-Konstanten
--------------------
- andere Werte als Integer sind möglich
- haben Adressen

enum-Konstanten
--------------------
- können in switch-statements benutzt werden
