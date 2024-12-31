#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "Event.h"

typedef struct EventQueueElement{
    Event* event;
    struct EventQueueElement* previous_element;
} EventQueueElement;


typedef struct {
    EventQueueElement* last_element;
    EventQueueElement* first_element;
    size_t current_size;
} EventQueue;

EventQueue* init_event_queue(void);

void free_queue(EventQueue* queue);
void free_event(Event* event);

void push_event_to_queue(Event* event, EventQueue* queue);
void create_and_push_event_to_queue(Event event, EventQueue* queue);

Event* pop_event_from_queue(EventQueue* queue);

void print_queue(EventQueue* queue);

#endif