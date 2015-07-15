#ifndef QP_HASHMAP_H
#define QP_HASHMAP_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>

#define FNV32_BASE ((unsigned int) 0x811c9dc5)
#define FNV32_PRIME ((unsigned int) 0x01000193)

// returns 1 if entry1 == entry2
typedef int (*hash_cmp_fn) (const void* entry1, const void* entry2,
        size_t len);
// used to compute hash codes
typedef unsigned int (*hash_fn) (const void* entry, size_t len);

typedef struct {
    void* key;
    void* value;
    unsigned int hash;
    int taken;
} table_entry;

typedef struct {
    table_entry* table;
    hash_cmp_fn cmp;
    hash_fn hash;
    size_t alloc;
    size_t items;
    size_t grow_at;
} hashmap;

typedef struct {
    hashmap* table;
    size_t curpos;
    table_entry entry;
} hashmap_iter;

// Read to go hash function
unsigned int memhash(const void *buf, size_t len)
{
    unsigned int hash = FNV32_BASE;
    unsigned char *ucbuf = (unsigned char *) buf;
    while (len--) {
        unsigned int c = *ucbuf++;
        hash = (hash * FNV32_PRIME) ^ c;
    }
    return hash;
}

int entrycmp (const void* e1, const void* e2, size_t len) {
    return memcmp(e1, e2, len);
}

void table_entry_init(table_entry* t) {
    t->taken = 0;
}

void table_entry_release(table_entry* t, int dynamic_entry) {
    if (t->taken && dynamic_entry) {
        free(t->key);
        free(t->value);
    }
    t->taken = 0;
}

size_t next_highest_two(size_t n) {
    size_t shift = 1;
    --n;
    while ((n + 1) & n) {
        n |= n >> shift;
        shift <<= 1;
    }
    return n + 1;
}

void hashmap_init(hashmap* m, hash_cmp_fn cmp, hash_fn hash, size_t hint) {
    m->cmp = cmp;
    m->hash = hash;
    size_t alloc = next_highest_two(hint);
    m->alloc = alloc;
    m->table = (table_entry*)malloc(sizeof(table_entry) * alloc);
    for (size_t i = 0; i < alloc; ++i)
        table_entry_init(&m->table[i]);
    m->items = 0;
    m->grow_at  = alloc * 0.6;
}

size_t bucket(hashmap* m, unsigned int hash) {
    return hash & (m->alloc - 1);
}

void rehash_insert(hashmap* m, table_entry t) {
    size_t i = bucket(m, t.hash);
    while (m->table[i].taken)
        i = bucket(m, i + 1);
    m->table[i] = t;
}

void rehash(hashmap* m) {
    table_entry* old = m->table;
    size_t old_alloc = m->alloc;
    m->alloc *= 2;
    m->table = (table_entry*)malloc(sizeof(table_entry) * m->alloc);
    for (size_t i = 0; i < m->alloc; ++i)
        table_entry_init(&m->table[i]);
    m->grow_at = m->alloc * 0.6;
    for (size_t i = 0; i < old_alloc; ++i)
        rehash_insert(m, old[i]);
    free(old);
}

void hashmap_insert(hashmap* m, void* key, void* value,
        size_t len) {
    size_t i = m->hash(key, len);
    table_entry e = {key, value, (unsigned int)i, 1};
    i = bucket(m, i);
    while (m->table[i].taken)
        i = bucket(m, i + 1);
    m->table[i] = e;
    m->items++;
    if (m->items >= m->grow_at)
        rehash(m);
}

void* hashmap_get(hashmap* m, void* key, size_t len) {
    size_t hash = m->hash(key, len);
    size_t i = bucket(m, hash);

    while (m->table[i].taken) {
        if (m->table[i].hash == hash)
            return m->table[i].value;
        i = bucket(m, i);
    }
    return NULL;
}

void hashmap_release(hashmap* m, int dynamic_entries) {
    for (size_t i = 0; i < m->alloc; ++i) {
        if (m->table[i].taken) {
            table_entry_release(&m->table[i], dynamic_entries);
        }
    }
    free(m->table);
    m->items = 0;
}

void hashmap_iter_begin(hashmap* m, hashmap_iter* i) {
    i->table = m;
    i->curpos = -1;
}

void hashmap_iter_next(hashmap_iter* i) {
    i->curpos++;
    while (!i->table->table[i->curpos].taken)
        i->curpos++;
    i->entry = i->table->table[i->curpos];
}

#endif
