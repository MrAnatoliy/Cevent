#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Event.h"
#include "../include/EventQueue.h"

EventQueue* init_event_queue(void){
    EventQueue *queue = malloc(sizeof(EventQueue));
    queue->first_element = NULL;
    queue->last_element = NULL;
    queue->current_size = 0;

    return queue;
}

void free_queue(EventQueue* queue){
    EventQueueElement* element = queue->last_element;

    // Iterate through all elements in the queue
    while (element != NULL) {
        EventQueueElement* element_to_free = element;
        element = element->previous_element;

        // Free the event data using the cleaner function
        if (element_to_free->event) {
            element_to_free->event->cleaner(element_to_free->event->data);
            free_event(element_to_free->event);
        }

        // Free the queue element itself
        free(element_to_free);
    }

    // Free the queue structure
    free(queue);
}

void free_event(Event* event) {
    if (event) {
        printf("Cleaning event %s\n", event->event_name);
        if (event->cleaner) {
            event->cleaner(event->data);
        }
        if (event->event_name) {
            free(event->event_name);
        }
        free(event);
        printf("Event was cleaned successfully\n\n");
    }
}

void push_event_to_queue(Event* event, EventQueue* queue){

    EventQueueElement* element = malloc(sizeof(EventQueueElement));
    if(element == NULL){
        perror("Can allocate memory for new queue element");
        return;
    }
    element->event = event;
    element->previous_element = NULL;

    if(queue->first_element == NULL || queue->last_element == NULL){
        queue->first_element = element;
        queue->last_element = element;
    } else {
        queue->first_element->previous_element = element;
        queue->first_element = element;            
    }

    queue->current_size++;
}

void create_and_push_event_to_queue(Event event, EventQueue* queue){
    Event* event_ptr = malloc(sizeof(Event));
    event_ptr->event_name = strdup(event.event_name);
    event_ptr->data = event.data;
    event_ptr->cleaner = event.cleaner;
    event_ptr->display = event.display;
    push_event_to_queue(event_ptr, queue);
}

Event* pop_event_from_queue(EventQueue* queue){
    if(queue->last_element == NULL){
        return NULL;
    } else {
        Event* event_to_pop = queue->last_element->event;
        EventQueueElement* element_to_free = queue->last_element;
        queue->last_element = queue->last_element->previous_element;
        free(element_to_free);
        queue->current_size--;

        return event_to_pop;
    }
}

void print_queue(EventQueue* queue){
    printf("Queue size : %d\n",queue->current_size);
    if(queue->current_size != 0) {
        EventQueueElement* element = queue->last_element;
        while (element != NULL) {
            printf("Event : [ %s ]\nData : [ %s ]\n",element->event->event_name, element->event->display(element->event->data));
            element = element->previous_element;
        }
        printf("\n");
    }
}