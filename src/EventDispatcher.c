#include <stdio.h>
#include <stdlib.h>

#include "../include/Event.h"
#include "../include/EventQueue.h"
#include "../include/EventDispatcher.h"
#include "../include/EventHandlerHashMap.h"

EventDispatcher* init_event_dispatcher(EventQueue* queue){
    EventDispatcher* dispatcher = malloc(sizeof(EventDispatcher));
    dispatcher->handlers_map = init_event_handler_hashmap();
    dispatcher->queue = queue;

    return dispatcher;
}

void add_new_handler(EventDispatcher* dispatcher, char* eventName, EventHandler handler){
    add_key_value_pair(dispatcher->handlers_map, eventName, handler);
}

void process_events(EventDispatcher* dispatcher){
    for(;;){
        Event* event;
        while ((event = pop_event_from_queue(dispatcher->queue)) != NULL) {
            EventHandler handler = get_value_by_key(dispatcher->handlers_map, event->event_name);
            if(handler != NULL){
                handler(event);
            } else {
                printf("Handler for %s was not found\n", event->event_name);
            }
            free_event(event);
        }
    }
}