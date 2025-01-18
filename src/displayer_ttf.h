#ifndef DISPLAYER_TTF_H
#define DISPLAYER_TTF_H
#define NbFonts 1000

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

struct DataTTF {int nb_fonts; int occupied; TTF_Font** fonts;};
typedef struct DataTTF DataTTF;

void free_font_database (DataTTF* database);

DataTTF* init_font_database();

int Load_TTF (DataTTF* database, char file_name[], int font_size);

void write_text(SDL_Renderer* render, DataTTF* font_database, int index_font, const char* text, int x, int y, SDL_Color text_color);

#endif