#include <stdio.h>
#include "vec.h"

typedef struct {
    const char *key;
    const char *val;
} KeyValuePair;

int main() {
    KeyValuePair *dict = NULL;
    
    vecPush(dict, (KeyValuePair) {
        .key = "Red", .val = "Rot"
    });
    vecPush(dict, (KeyValuePair) {
        .key = "Green", .val = "Grün"
    });
    vecPush(dict, (KeyValuePair) {
        .key = "Blue", .val = "Blau"
    });
    
    vecForEach(KeyValuePair *e, dict) {
        printf("%s\t->\t%s\n", e->key, e->val);
    }
    
    vecDrop(dict);
}
