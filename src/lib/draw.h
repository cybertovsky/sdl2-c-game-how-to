#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *text, int x, int y);
void draw_text_center(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *text, int w, int h, int off_x, int off_y);
void draw_score(SDL_Renderer *renderer, TTF_Font *font, int score);
void draw_sprite(SDL_Renderer *renderer, struct Sprite sprite);
