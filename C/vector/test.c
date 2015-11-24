#include <stdio.h>
#include "vector.h"

int main() {
    vector* v = vector_ctor(1, sizeof(int));

    int x = 5;
    vector_push_back(v, &x);
    ++x;
    vector_push_back(v, &x);
    ++x;
    vector_push_back(v, &x);
    vector_push_back(v, &x);

    printf("%d\n", *(int*)vector_get(v, 0));
    printf("%d\n", *(int*)vector_get(v, 1));
    printf("%d\n", *(int*)vector_get(v, 2));

    vector_dtor(v);
    return 0;
}
