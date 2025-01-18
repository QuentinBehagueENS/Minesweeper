#include "events_management.h"

EventManager* init_event_manager(){
    EventManager* rep = (EventManager*)malloc(sizeof(EventManager));
    rep->key_events = (bool*)malloc(KEY_EVENT_NUMBER*sizeof(bool));
    rep->key_states = (bool*)malloc(KEY_STATE_NUMBER*sizeof(bool));
    for(int i = 0; i < KEY_EVENT_NUMBER; i++){
        rep->key_events[i] = false;
    }
    for(int i = 0; i < KEY_STATE_NUMBER; i++){
        rep->key_states[i] = false;
    }
    rep->mouse_x = 0;
    rep->mouse_y = 0;
    rep->mouse_wheel = 0;
    return rep;
}

void free_event_manager (EventManager* manager){
    free(manager->key_events);
    free(manager->key_states);
    free(manager);
}

void reinit_loop(EventManager* event_manager){
    event_manager->mouse_wheel = 0;
    for(int i = 0; i < KEY_EVENT_NUMBER; i++){
        event_manager->key_events[i] = false;
    }
}

bool update_event_manager (EventManager* event_manager, SDL_Event event){
    reinit_loop(event_manager);
    SDL_GetMouseState(&event_manager->mouse_x, &event_manager->mouse_y);
    if (event.type == SDL_KEYUP){
        if(event.key.keysym.sym == SDLK_UP){
            event_manager->key_states[KEY_UP_DOWN] = false;
        }
        if(event.key.keysym.sym == SDLK_DOWN){
            event_manager->key_states[KEY_DOWN_DOWN] = false;
        }
        if(event.key.keysym.sym == SDLK_LEFT){
            event_manager->key_states[KEY_LEFT_DOWN] = false;
        }
        if(event.key.keysym.sym == SDLK_RIGHT){
            event_manager->key_states[KEY_RIGHT_DOWN] = false;
        }
        if(event.key.keysym.sym == SDLK_SPACE){
            event_manager->key_states[KEY_SPACE_DOWN] = false;
        }
    }
    if (event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_UP){
            event_manager->key_events[KEY_UP] = true;
            event_manager->key_states[KEY_UP_DOWN] = true;
        }
        if(event.key.keysym.sym == SDLK_DOWN){
            event_manager->key_events[KEY_DOWN] = true;
            event_manager->key_states[KEY_DOWN_DOWN] = true;
        }
        if(event.key.keysym.sym == SDLK_LEFT){
            event_manager->key_events[KEY_LEFT] = true;
            event_manager->key_states[KEY_LEFT_DOWN] = true;
        }
        if(event.key.keysym.sym == SDLK_RIGHT){
            event_manager->key_events[KEY_RIGHT] = true;
            event_manager->key_states[KEY_RIGHT_DOWN] = true;
        }
        if(event.key.keysym.sym == SDLK_SPACE){
            event_manager->key_events[KEY_SPACE] = true;
            event_manager->key_states[KEY_SPACE_DOWN] = true;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT){
            event_manager->key_states[MOUSE_LEFT_DOWN] = true;
            event_manager->key_events[MOUSE_BUTTON_LEFT_DOWN] = true;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT ){
            event_manager->key_states[MOUSE_RIGHT_DOWN] = true;
            event_manager->key_events[MOUSE_BUTTON_RIGHT_DOWN] = true;
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT){
            event_manager->key_states[MOUSE_LEFT_DOWN] = false;
            event_manager->key_events[MOUSE_BUTTON_LEFT_UP] = true;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT){
            event_manager->key_states[MOUSE_RIGHT_DOWN] = false;
            event_manager->key_events[MOUSE_BUTTON_RIGHT_UP] = true;
        }
    }
    if (event.type == SDL_MOUSEWHEEL){
        event_manager->mouse_wheel = event.wheel.y;
        //zoom(grid, event_manager->mouse_wheel, event_manager->mouse_x, event_manager->mouse_y);
    }
    if (event.type == SDL_MOUSEMOTION){
        return true;
    }
    if (event.type == SDL_QUIT){
        return false;
    }
    return true;
}
