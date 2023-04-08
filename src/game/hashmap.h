#ifndef GAME_HASHMAP_H
#define GAME_HASHMAP_H

#define HASHMAP_TABLE_SIZE 1000

typedef struct {

    void *key;
    void *value;

} HashMapEntry;

typedef struct {

    HashMapEntry **entries;
    int size;

} HashMap;

unsigned long hashmap_generate_hash (void *key);

HashMap *hashmap_create (int capacity);
void hashmap_free (HashMap *hashmap);

void hashmap_put (HashMap *hashmap, void *key, void *value);
void *hashmap_get (HashMap *hashmap, void *key);
void hashmap_remove (HashMap *hashmap, void *key);

void hashmap_clear (HashMap *hashmap);

#endif