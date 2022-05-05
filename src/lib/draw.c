#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "sprite.h"

void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *text, int x, int y)
{
    SDL_Surface *surface_score = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);
    int texW, texH;
    SDL_QueryTexture(score_texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, score_texture, NULL, &dstrect);
}

void draw_text_center(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *text, int w, int h, int off_x, int off_y)
{
    SDL_Surface *surface_score = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);
    int texW, texH;
    SDL_QueryTexture(score_texture, NULL, NULL, &texW, &texH);
    int x = (int)((w - texW) / 2) + off_x;
    int y = (int)((h - texH) / 2) + off_y;
    SDL_Rect dstrect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, score_texture, NULL, &dstrect);
}

void draw_score(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    char score_text[20];
    sprintf(score_text, "%d", score);
    SDL_Color color = {255, 0, 0};
    draw_text(renderer, font, color, score_text, 10, 10);
}

void draw_sprite(SDL_Renderer *renderer, struct Sprite sprite)
{
    SDL_Rect rect = {sprite.x, sprite.y, sprite.w, sprite.h};
    SDL_RenderCopy(renderer, sprite.texture, NULL, &rect);
}