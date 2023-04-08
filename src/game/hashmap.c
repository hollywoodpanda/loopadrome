#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

unsigned long hashmap_generate_hash (void *key) 
{
    unsigned int size = sizeof(key);
    unsigned long hash = (*(unsigned long*)key) % size;
    return hash;
}

HashMap *hashmap_create (int capacity) 
{
    HashMap *hashmap = malloc(sizeof(HashMap));
    hashmap->entries = (HashMapEntry**)calloc(capacity, sizeof(HashMapEntry*));
    hashmap->size = capacity;
    return hashmap;
}

void hashmap_free (HashMap *hashmap) 
{

    hashmap_clear(hashmap);
    free(hashmap->entries);
    free(hashmap);

}

void hashmap_put (HashMap *hashmap, void *key, void *value) 
{

    unsigned long entry_index = hashmap_generate_hash(key) % hashmap->size;

    while (hashmap->entries[entry_index] != NULL) {
        
        if (memcmp(hashmap->entries[entry_index]->key, key, sizeof(key)) == 0) {
            hashmap->entries[entry_index]->value = value;
            return;
        }

        entry_index = (entry_index + 1) % hashmap->size;

    }

    hashmap->entries[entry_index] = (HashMapEntry*) malloc(sizeof(HashMapEntry));
    hashmap->entries[entry_index]->key = key;
    hashmap->entries[entry_index]->value = value;
    
}

void *hashmap_get (HashMap *hashmap, void *key) 
{
    
    unsigned long entry_index = hashmap_generate_hash(key) % hashmap->size;

    while (hashmap->entries[entry_index] != NULL) {
        
        if (memcmp(hashmap->entries[entry_index]->key, key, sizeof(key)) == 0) {
            return hashmap->entries[entry_index]->value;
        }

        entry_index = (entry_index + 1) % hashmap->size;

    }

    return NULL;

}

void hashmap_remove (HashMap *hashmap, void *key) 
{

    unsigned long entry_index = hashmap_generate_hash(key) % hashmap->size;

    while (hashmap->entries[entry_index] != NULL) {
        
        if (memcmp(hashmap->entries[entry_index]->key, key, sizeof(key)) == 0) {
            free(hashmap->entries[entry_index]->key);
            free(hashmap->entries[entry_index]->value);
            free(hashmap->entries[entry_index]);
            hashmap->entries[entry_index] = NULL;
            return;
        }

        entry_index = (entry_index + 1) % hashmap->size;

    }

}

void hashmap_clear (HashMap *hashmap) 
{

    for (int i = 0; i < hashmap->size; i++) {
        if (hashmap->entries[i] != NULL) {
            hashmap_remove(hashmap, hashmap->entries[i]->key);
        }
    }

}
