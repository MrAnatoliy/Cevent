#ifndef EVENT_HANDLER_HASH_MAP_H
#define EVENT_HANDLER_HASH_MAP_H

#include "../include/EventHandler.h"

#define INITIAL_HASHMAP_CAPACITY 64
#define HASHMAP_FILL_THRESHOLD 0.5 // 50% fill threshold

typedef struct {
    enum EKeyState {
        EMPTY,
        DELETED,
        OCCUPIED,
    } state;
    char* key; // Store the key here for comparison during retrieval
} HashMapMetadata;

typedef struct {
    EventHandler* data;
    HashMapMetadata* metadata;
    int hashmap_current_amount;
    int hashmap_capacity;
} EventHandlerHashMap;

EventHandlerHashMap* init_event_handler_hashmap(void);
void add_key_value_pair(EventHandlerHashMap* map,char* key, EventHandler value);
EventHandler get_value_by_key(EventHandlerHashMap* map,char* key);
void delete_key_value_pair(EventHandlerHashMap* map,char* key);

#endif