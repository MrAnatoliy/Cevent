#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Event.h"
#include "include/EventQueue.h"
#include "include/EventHandler.h"
#include "include/EventDispatcher.h"

//-------------------------------
//Example 

enum ETempMesureSystem {
    CELSIUS,
    FARENHEIT,
    KELVIN
};

struct TemperatureData
{
    float degree;
    enum ETempMesureSystem mesure_system;
    char* mesure_time;
};

void free_temperature_data(void* data) {
    struct TemperatureData* t_data = (struct TemperatureData*)data;
    free(t_data->mesure_time);
    free(t_data);
}

char* display_temperature_data(void* data) {
    struct TemperatureData* t_data = (struct TemperatureData*)data;
    char mesure_system_str[32];
    switch (t_data->mesure_system) {
        case CELSIUS:
            strcpy(mesure_system_str, "C");
            break;
        case FARENHEIT:
            strcpy(mesure_system_str, "F");
            break;
        case KELVIN:
            strcpy(mesure_system_str, "K");
            break;
        default:
            strcpy(mesure_system_str, "Unknown mesure system");
            break;
    }

    char* s_data = malloc(128);
    sprintf(s_data, "degree : %f %s, mesure time : %s", t_data->degree, mesure_system_str, t_data->mesure_time);
    return s_data;
}

void temperatureHandler(Event* event){
    struct TemperatureData* t_data = (struct TemperatureData*)event->data;
    printf("Temperature %f is to high. enabling cooling system...\n",t_data->degree);
}

char* display_o2_data(void* data){
    return (char*)data;
}

void free_02_data(void* data){
    free(data);
}


int main(void) {
    
    /*
    
    TODO

    Event -> EventQueue

    Dispatcher pull event from quere and send to the corresponding event handler

    Handler process event

    Just singlethreaded for now

    */

    EventQueue* queue = init_event_queue();
    struct TemperatureData* t_data = malloc(sizeof(struct TemperatureData));

    t_data->degree = 28.300000f;
    t_data->mesure_system = CELSIUS;
    t_data->mesure_time = strdup("15:03:23");
    create_and_push_event_to_queue((Event)
    {
        .event_name = "HIGH_TEMP", 
        .data = t_data, 
        .cleaner = free_temperature_data, 
        .display = display_temperature_data
    }, queue);

    char* o2 = strdup("o2 : 134");

    create_and_push_event_to_queue((Event)
    {
        .event_name = "LOW_O2", 
        .data = o2,
        .cleaner = free_02_data, 
        .display = display_o2_data
    }, queue);

    print_queue(queue);


    EventDispatcher* dispatcher = init_event_dispatcher(queue);
    add_new_handler(dispatcher, "HIGH_TEMP", temperatureHandler);
    process_events(dispatcher);

    free_queue(queue);
    
    return 0;
}