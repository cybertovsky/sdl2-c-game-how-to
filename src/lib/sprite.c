
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"

SDL_Surface *load_image(char *path)
{
    SDL_Surface *image = IMG_Load(path);
    if (!image)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        exit(0);
    }

    Uint32 colorkey = SDL_MapRGB(image->format, 255, 255, 255);
    // enables transparency for all white pixels
    SDL_SetColorKey(image, SDL_TRUE, colorkey);
    return image;
}

struct Sprite make_sprite(SDL_Renderer *renderer, int x, int y, int w, int h, int speed, int die, char *path)
{
    SDL_Surface *surface = load_image(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    struct Sprite sprite = {x, y, w, h, 0, 0, speed, die, surface, texture};
    return sprite;
}

void stay_on_screen(struct Sprite *sprite, int width, int height)
{
    if ((*sprite).y <= 0)
    {
        (*sprite).y = 0;
    }
    if ((*sprite).y >= height - (*sprite).h)
    {
        (*sprite).y = height - (*sprite).h;
    }
    if ((*sprite).x <= 0)
    {
        (*sprite).x = 0;
    }
    if ((*sprite).x >= width - (*sprite).w)
    {
        (*sprite).x = width - (*sprite).w;
    }
    // return sprite;
}

bool check(struct Sprite a, struct Sprite b)
{
    if (abs(a.x - b.x) < a.w)
    {
        if (abs(a.y - b.y) < a.h)
        {
            return 1;
        }
    }
    return 0;
}