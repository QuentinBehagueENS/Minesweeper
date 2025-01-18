#ifndef EVENTS_MANAGEMENT_H
#define EVENTS_MANAGEMENT_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KEY_EVENT_NUMBER 19
#define KEY_STATE_NUMBER 7

enum KeyEvent{
    MOUSE_BUTTON_RIGHT_UP,
    MOUSE_BUTTON_RIGHT_DOWN,
    MOUSE_BUTTON_LEFT_UP,
    MOUSE_BUTTON_LEFT_DOWN,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE,
    NUM0,
    NUM1,
    NUM2,
    NUM3,
    NUM4,
    NUM5,
    NUM6,
    NUM7,
    NUM8,
    NUM9,
};
typedef enum KeyEvent KeyEvent;

enum KeyStates{
    MOUSE_LEFT_DOWN,
    MOUSE_RIGHT_DOWN,
    KEY_UP_DOWN,
    KEY_DOWN_DOWN,
    KEY_LEFT_DOWN,
    KEY_RIGHT_DOWN,
    KEY_SPACE_DOWN,
};
typedef enum KeyStates KeyStates;

struct EventManager {int mouse_x; int mouse_y; int mouse_wheel; bool* key_events; bool* key_states;};
typedef struct EventManager EventManager;

EventManager* init_event_manager();

void free_event_manager (EventManager* manager);

void reinit_loop(EventManager* event_manager);

bool update_event_manager (EventManager* event_manager, SDL_Event event);

#endif