#include "board.h"
#include "display.h"
#include "events_management.h"
#include "SDL2_gfxPrimitives.h"
#include "displayer_ttf.h"

#define WINDOW_WIDTH 625
#define WINDOW_HEIGHT 625
#define MARGIN 18
#define SQUARE_SIZE 134
#define FPS_LIMIT 30
#define BACKGROUND_COLOR (SDL_Color){187, 173, 160, 255}
#define TXT_COLOR1 (SDL_Color){119, 110, 101, 255}
#define TXT_COLOR2 (SDL_Color){249, 246, 242, 255}
#define RADIUS 3
#define WINDOW_TITLE "2048"
#define ICON_PATH "./2048.bmp"
#define FONT_PATH "./font.ttf"
#define HEX_TO_SDL_COLOR(hex) (SDL_Color){((hex >> 16) & 0xFF), ((hex >> 8) & 0xFF), (hex & 0xFF), 255}

SDL_Color colors[12] = {
    (SDL_Color){205, 193, 180, 255}, 
    (SDL_Color){238, 228, 218, 255}, 
    (SDL_Color){237, 224, 200, 255}, 
    (SDL_Color){242, 177, 121, 255}, 
    (SDL_Color){245, 149, 99, 255}, 
    (SDL_Color){246, 124, 95, 255}, 
    (SDL_Color){246, 94, 59, 255}, 
    (SDL_Color){237, 207, 114, 255},
    (SDL_Color){237, 204, 97, 255},
    (SDL_Color){237, 200, 81, 255},
    (SDL_Color){237, 197, 63, 255},
    (SDL_Color){237, 194, 46, 255}
};

SDL_Color txt_colors[12] = {
    TXT_COLOR1, 
    TXT_COLOR1,
    TXT_COLOR1,
    TXT_COLOR2, 
    TXT_COLOR2, 
    TXT_COLOR2, 
    TXT_COLOR2, 
    TXT_COLOR2,
    TXT_COLOR2,
    TXT_COLOR2,
    TXT_COLOR2,
    TXT_COLOR2
};

char* txt[14] = {"0","2","4","8","16","32","64","128","256","512","1024","2048", "4096", "8192"};

int txt_index[14] = {0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 3};

int x_margin[14] = {
    0, 
    SQUARE_SIZE/3 + SQUARE_SIZE/30,
    SQUARE_SIZE/3 + SQUARE_SIZE/30, 
    SQUARE_SIZE/3 + SQUARE_SIZE/30,
    8*SQUARE_SIZE/40, 
    9*SQUARE_SIZE/40,
    9*SQUARE_SIZE/40, 
    SQUARE_SIZE/8, 
    SQUARE_SIZE/8, 
    SQUARE_SIZE/8, 
    SQUARE_SIZE/10,
    SQUARE_SIZE/10,
    SQUARE_SIZE/10,
    SQUARE_SIZE/10
};

int y_margin[14] = {
    0,
    7*SQUARE_SIZE/24,
    7*SQUARE_SIZE/24,
    7*SQUARE_SIZE/24,
    7*SQUARE_SIZE/24, 
    7*SQUARE_SIZE/24,
    7*SQUARE_SIZE/24, 
    7*SQUARE_SIZE/22, 
    7*SQUARE_SIZE/22, 
    7*SQUARE_SIZE/22, 
    8*SQUARE_SIZE/22,
    8*SQUARE_SIZE/22,
    8*SQUARE_SIZE/22,
    8*SQUARE_SIZE/22
};

EventManager* event_manager;
SDL_Window *window = NULL; 
SDL_Renderer *renderer = NULL;
SDL_Surface* icon;
DataTTF* global_font;

void display_grid(board* b){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            int c = get(b, (3-i)*WIDTH + (3-j));
            roundedBoxRGBA(renderer, (j+1)*MARGIN + j*SQUARE_SIZE, (i+1)*MARGIN + i*SQUARE_SIZE, (j+1)*MARGIN + (j+1)*SQUARE_SIZE,  (i+1)*MARGIN + (i+1)*SQUARE_SIZE, RADIUS, colors[c].r, colors[c].g, colors[c].b, 255);
            if(c != 0){
                 write_text(renderer, global_font, txt_index[c], txt[c], (j+1)*MARGIN + j*SQUARE_SIZE + x_margin[c], (i+1)*MARGIN + i*SQUARE_SIZE+ y_margin[c], txt_colors[c]);
            }
        }
    }
}

void start_engine(){
    init_SDL();
    TTF_Init();
    srand(time(NULL));
    icon = SDL_LoadBMP(ICON_PATH); 
    event_manager = init_event_manager();
    global_font = init_font_database();
    Load_TTF(global_font, FONT_PATH, 70);
    Load_TTF(global_font, FONT_PATH, 65);
    Load_TTF(global_font, FONT_PATH, 60);
    Load_TTF(global_font, FONT_PATH, 50);
    Load_TTF(global_font, FONT_PATH, 60);
    TEST(icon != NULL);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_SHOWN , &window, &renderer);
    SDL_SetWindowTitle(window, WINDOW_TITLE);
    SDL_SetWindowIcon(window, icon);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void shutdown_engine(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free_event_manager(event_manager);
    free_font_database(global_font);
    SDL_FreeSurface(icon);
    TTF_Quit();
    SDL_Quit();
}

void SDL_Loop (){
    bool window_open = true;
    board* b = random_initial_board();
    display_board(b);
    int loop_beginning_time;
    int loop_ending_time;
    int refresh = false;
    draw_fill_rectangle(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR);
    display_grid(b);
    SDL_RenderPresent(renderer);
    while(window_open){
        loop_beginning_time = SDL_GetTicks();
        SDL_Event event;
        // Check for events :
        while(SDL_PollEvent(&event) && window_open){
            window_open = update_event_manager(event_manager, event);
            if(event.type != SDL_MOUSEMOTION){
                if(event_manager->key_events[KEY_UP]){
                    refresh = play_move(b, DOWN);
                }
                else if(event_manager->key_events[KEY_DOWN]){
                    refresh = play_move(b, UP);
                }
                else if(event_manager->key_events[KEY_LEFT]){
                    refresh = play_move(b, RIGHT);
                }
                else if(event_manager->key_events[KEY_RIGHT]){
                    refresh = play_move(b, LEFT);
                }
                display_board(b);
            }
        }
        if(refresh){
            draw_fill_rectangle(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BACKGROUND_COLOR);
            display_grid(b);
            SDL_RenderPresent(renderer);
            refresh = false;
        }
        loop_ending_time = SDL_GetTicks();
        if (loop_ending_time - loop_beginning_time < FPS_LIMIT){
            SDL_Delay(FPS_LIMIT - (loop_ending_time - loop_beginning_time));
        }
    }
}

int main(int argc, char *argv[]){
    FreeConsole();
    start_engine();
    SDL_Loop();
    shutdown_engine();
    return EXIT_SUCCESS;
}


/* Compilation commands :
    - gcc -Wall src\*.c bin\resources.o -o bin\2048.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows
    - cd Programmation/2048
*/