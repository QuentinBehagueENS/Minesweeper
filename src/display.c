#include "display.h"


void SDL_ExitWithError(const char *message){
    SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void init_SDL(){
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("SDL V%d.%d.%d\n", nb.major, nb.minor, nb.patch);
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialization failure : SDL2");
    }
}

void set_pixel(SDL_Renderer* render, int x, int y){
    if(SDL_RenderDrawPoint(render, x, y) != 0){
        SDL_ExitWithError("Set Pixel Color Failure");
    }
}

void draw_line(SDL_Renderer* render, int x1, int y1, int x2, int y2, SDL_Color color){
    if(SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a) != 0){
        SDL_ExitWithError("Set Color Failure");
    }
    if(SDL_RenderDrawLine(render, x1, y1, x2, y2) != 0){
        SDL_ExitWithError("Draw Line Failure");
    }
}

void draw_rectangle(SDL_Renderer* render, int x1, int y1, int x2, int y2, SDL_Color color){
    assert(x1 < x2 && y1 < y2);
    SDL_Rect rectangle;
    rectangle.x = x1;
    rectangle.y = y1;
    rectangle.w = x2 - x1;
    rectangle.h = y2 - y1;
    if(SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a) != 0){
        SDL_ExitWithError("Set Color Failure");
    }
    if(SDL_RenderDrawRect(render, &rectangle) != 0 ){
        SDL_ExitWithError("Draw Rectangle Failure");
    }
}

void draw_fill_rectangle(SDL_Renderer* render, int x1, int y1, int x2, int y2, SDL_Color color){
    if(x1 == x2 || y1 == y2){
        return;
    }
    assert(x1 < x2 && y1 < y2);
    SDL_Rect rectangle;
    rectangle.x = x1;
    rectangle.y = y1;
    rectangle.w = x2 - x1;
    rectangle.h = y2 - y1;
    if(SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a) != 0){
        SDL_ExitWithError("Set Color Failure");
    }
    if(SDL_RenderFillRect(render, &rectangle) != 0 ){
        SDL_ExitWithError("Draw Rectangle Failure");
    }
}

void draw_circle(SDL_Renderer* render, int x0, int y0, int radius, SDL_Color color){
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    if(SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a) != 0){
        SDL_ExitWithError("Set Color Failure");
    }

    while (x >= y){
        set_pixel(render, x0 + x, y0 + y);
        set_pixel(render, x0 + y, y0 + x);
        set_pixel(render, x0 - y, y0 + x);
        set_pixel(render, x0 - x, y0 + y);
        set_pixel(render, x0 - x, y0 - y);
        set_pixel(render, x0 - y, y0 - x);
        set_pixel(render, x0 + y, y0 - x);
        set_pixel(render, x0 + x, y0 - y);
        


        if (err <= 0){
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0){
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void draw_fill_circle(SDL_Renderer* render, int x0, int y0, int radius, SDL_Color color){
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    if(SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a) != 0){
        SDL_ExitWithError("Set Color Failure");
    }

    while (x >= y){
        draw_line(render, x0 + y, y0 + x, x0 - y, y0 + x, color);
        draw_line(render, x0 - x, y0 + y, x0 + x, y0 + y, color);
        draw_line(render, x0 - y, y0 - x, x0 + y, y0 - x, color);
        draw_line(render, x0 - x, y0 - y, x0 + x, y0 - y, color);
        if (err <= 0){
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0){
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}
