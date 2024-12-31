#ifndef EVENT_H
#define EVENT_H

typedef void (*DataCleaner)(void*);
typedef char* (*DataDispay)(void*);

typedef struct {
    char* event_name;
    void* data;
    DataCleaner cleaner;
    DataDispay display;
    void * context;
} Event;

#endif