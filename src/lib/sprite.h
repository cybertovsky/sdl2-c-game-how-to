#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

struct Sprite
{
    int x;
    int y;
    int w;
    int h;
    int vx;
    int vy;
    int speed;
    int die;
    SDL_Surface *surface;
    SDL_Texture *texture;
};

struct Sprite make_sprite(SDL_Renderer *renderer, int x, int y, int w, int h, int speed, int die, char *path);
void stay_on_screen(struct Sprite *sprite, int width, int height);
bool check(struct Sprite a, struct Sprite b);