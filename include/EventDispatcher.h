#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "../include/Event.h"
#include "../include/EventQueue.h"
#include "../include/EventHandler.h"
#include "../include/EventHandlerHashMap.h"

typedef struct {
    EventQueue* queue;
    EventHandlerHashMap* handlers_map;
} EventDispatcher;

EventDispatcher* init_event_dispatcher(EventQueue* queue);
void add_new_handler(EventDispatcher* dispatcher, char* eventName, EventHandler handler);

void process_events(EventDispatcher* dispatcher);
void process_single_event(EventDispatcher* dispatcher);

void free_dispatcher(EventDispatcher* dispatcher);

#endif