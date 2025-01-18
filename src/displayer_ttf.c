//########################################################################################################################################################// 
//##########################################################//   Writting functions  //###################################################################//
//########################################################################################################################################################//

#include "displayer_ttf.h"

DataTTF* init_font_database(){
    DataTTF* rep = (DataTTF*)malloc(sizeof(DataTTF));
    rep->nb_fonts = NbFonts;
    rep->occupied = 0;
    rep->fonts = (TTF_Font**)malloc(NbFonts*sizeof(TTF_Font*));
    return rep;
}

void free_font_database (DataTTF* database){
    for(int i = 0; i < database->occupied; i++){
        TTF_CloseFont(database->fonts[i]);
    }
    free(database->fonts);
    free(database);
}

int Load_TTF (DataTTF* database, char file_name[], int font_size){
    database->fonts[database->occupied] = TTF_OpenFont(file_name, font_size);
    database->occupied ++;
    return database->occupied - 1;
}

void write_text(SDL_Renderer* render, DataTTF* font_database, int index_font, const char* text, int x, int y, SDL_Color text_color){
    assert(index_font < font_database->occupied);
    SDL_Surface* text_surface = TTF_RenderText_Blended(font_database->fonts[index_font], text, text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(render, text_surface);
    SDL_FreeSurface(text_surface);
    int text_width, text_height;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);
    int text_x = x ;
    int text_y = y ;
    SDL_Rect text_rect = {text_x, text_y, text_width, text_height};
    SDL_RenderCopy(render, text_texture, NULL, &text_rect);
    SDL_DestroyTexture(text_texture);   
}
