#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char* data;
    size_t size;
    size_t alloc;
    size_t dsize;
} vector;

vector* vector_ctor(size_t hint, size_t dsize) {
    vector* v = (vector*)malloc(sizeof(vector));
    v->data = (unsigned char*)malloc(hint * dsize);
    v->dsize = dsize;
    v->alloc = hint;
    v->size = 0;

    return v;
}

void vector_push_back(vector* const self, void* v) {
    if (self->size == self->alloc) {
        self->alloc *= 2;
        self->data = (unsigned char*)realloc(self->data, self->alloc * self->dsize);
    }

   memcpy(self->data + (self->size * self->dsize), v, self->dsize);
   ++self->size;
}

void* vector_get(vector const * const self, size_t i) {
    return &self->data[self->dsize * i];
}

void vector_set(vector* const self, size_t i, void* e) {
    memcpy(self->data + (i * self->dsize), e, self->dsize);
}

void vector_pop_back(vector* const self) {
    --self->size;
}

void vector_dtor(vector* self) {
    free(self->data);
    free(self);
}
