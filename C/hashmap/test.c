#include "hashmap.h"
#include <string.h>
#include <stdio.h>


typedef struct {
    int x;
    int y;
} point;

int main() {
    hashmap m;

    hashmap_init(&m, entrycmp, memhash, 64);
    int five = 5;
    hashmap_insert(&m, &five, "hello", sizeof(int));
    void* x = hashmap_get(&m, &five, sizeof(int));
    printf("%s\n", (char*)x);

    point p;
    p.x = 5;
    p.y = 10;


    char dude[] = "dude";
    int len = strlen(dude);
    hashmap_insert(&m, dude, &p, len);
    void* z = hashmap_get(&m, dude, len);
    point* data = (point*)z;
    printf("%d %d\n", data->x, data->y);

    hashmap_release(&m, 0);
    return 0;
}
