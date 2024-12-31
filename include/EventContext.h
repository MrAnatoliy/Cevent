#ifndef EVENT_CONTEXT_H
#define EVENT_CONTEXT_H

#include "../include/EventQueue.h"

typedef struct {
    EventQueue* queue;
    // further context
} EventContext;

#endif