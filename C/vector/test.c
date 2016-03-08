#include <stdio.h>
#include "vector.h"

int main() {
    vector* v = vector_ctor(1, int);

    // even tho x falls out of scope the vector
    // entries remain valid since I do a byte copy
    {
        int x = 5;
        vector_push_back(v, x);
        ++x;
        vector_push_back(v, x);
        ++x;
        vector_push_back(v, x);
        vector_push_back(v, x);
    }

    printf("%d\n", vector_get(v, 0, int));
    printf("%d\n", vector_get(v, 1, int));
    printf("%d\n", vector_get(v, 2, int));
    vector_dtor(v);

    vector* v2 = vector_ctor(1, char*);
    char* s = "hello";
    vector_push_back(v, s);
    printf("%s\n", vector_get(v, 0, char*));
    vector_dtor(v2);
    return 0;
}
