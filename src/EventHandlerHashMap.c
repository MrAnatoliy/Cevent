#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/EventHandlerHashMap.h"

#define calc_hash(key, map, hash) do { \
    const char* _c = (const char*)(key); \
    *(hash) = 0; \
    while (*_c != '\0') { \
        *(hash) = ((*(hash) << 5) - *(hash)) + (*_c); \
        _c++; \
    } \
    *(hash) = *(hash) % (map)->hashmap_capacity; \
} while(0)

EventHandlerHashMap* init_event_handler_hashmap(void){
    EventHandlerHashMap* map = malloc(sizeof(EventHandlerHashMap));
    if(map == NULL){
        printf("Cant allocate memory for new hashmap");
        return NULL;
    }
    map->data = malloc(sizeof(EventHandler) * INITIAL_HASHMAP_CAPACITY);
    if(map->data == NULL){
        printf("Cant allocate memory for hashmap data");
        return NULL;
    }
    map->metadata = malloc(sizeof(HashMapMetadata) * INITIAL_HASHMAP_CAPACITY);
    if(map->metadata == NULL){
        printf("Cant allocate memory for hashmap metadata");
        return NULL;
    }
    map->hashmap_capacity = INITIAL_HASHMAP_CAPACITY;
    map->hashmap_current_amount = 0;

    return map;
}

void add_key_value_pair(EventHandlerHashMap* map, char* key, EventHandler value) {
    if (map->data == NULL || map->metadata == NULL) {
        printf("Map data or metadata is NULL\n");
        return;
    }

    if ((float)map->hashmap_current_amount / (float)map->hashmap_capacity > HASHMAP_FILL_THRESHOLD) {
        // TODO: Resize and rehash the hash map
        return;
    }

    size_t hash = 0;
    calc_hash(key, map, &hash);

    size_t original_hash = hash;
    size_t step = 1; // Quadratic step starts at 1
    size_t i = 0;

    while (map->metadata[hash].state == OCCUPIED) {
        if (strcmp(map->metadata[hash].key, key) == 0) {
            // Key already exists, replace the value
            map->data[hash] = value;
            return;
        }

        // Quadratic probing: Move to the next index
        i++;
        hash = (original_hash + i * i) % map->hashmap_capacity;

        // Detect full circle
        if (i >= map->hashmap_capacity) {
            printf("Hash map is full, cannot insert key: %s\n", key);
            return;
        }
    }

    // Insert the new key-value pair
    map->data[hash] = value;
    map->metadata[hash].state = OCCUPIED;
    map->metadata[hash].key = strdup(key); // Store a copy of the key
    map->hashmap_current_amount++;
}

EventHandler get_value_by_key(EventHandlerHashMap* map, char* key) {

    // TODO improve HashMapMetaData by adding pointer to next occupied index

    if (map == NULL || map->data == NULL || map->metadata == NULL) {
        printf("Map or its internal structures are NULL\n");
        return NULL;
    }

    size_t hash = 0;
    calc_hash(key, map, &hash);

    size_t original_hash = hash; // To detect cycles during probing
    while (map->metadata[hash].state != EMPTY) {
        if (map->metadata[hash].state == OCCUPIED) {
            if (strcmp(map->metadata[hash].key, key) == 0) {
                return map->data[hash];
            }
        }
        hash++;
        hash %= map->hashmap_capacity;

        if (hash == original_hash) {
            break; // We've come full circle
        }
    }

    // Key not found
    return NULL;
}

void delete_key_value_pair(EventHandlerHashMap* map, char* key) {
    if (map == NULL || map->data == NULL || map->metadata == NULL) {
        printf("Map or its internal structures are NULL\n");
        return;
    }

    size_t hash = 0;
    calc_hash(key, map, &hash);

    size_t original_hash = hash;
    while (map->metadata[hash].state != EMPTY) {
        if (map->metadata[hash].state == OCCUPIED) {
            if (strcmp(map->metadata[hash].key, key) == 0) {
                free(map->metadata[hash].key); // Free the stored key
                map->metadata[hash].state = DELETED;
                map->data[hash] = NULL;       // Clear the value
                map->hashmap_current_amount--;
                return;
            }
        }
        hash++;
        hash %= map->hashmap_capacity;

        if (hash == original_hash) {
            break; // Full circle
        }
    }

    printf("Key not found\n");
}