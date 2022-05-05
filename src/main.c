#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sprite.h"
#include "lib/draw.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 400;

void bg(SDL_Renderer *renderer)
{
    SDL_Rect bg_color = {0, 0, 640, 480};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bg_color);
}

int main(int argc, char **argv)
{
    int loop_time = 0;
    int game_status = 0; // ready  1 glaying 2 pause 3 gameover
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    SDL_Window *screen = SDL_CreateWindow("demo",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    // SDL_SetWindowFullscreen(screen, 1);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    // sprites
    struct Sprite hero = make_sprite(renderer, (int)(WINDOW_WIDTH / 2 - 99 / 4), WINDOW_HEIGHT - 123 / 2 - 10, (int)(99 / 2), (int)(123 / 2), 2, 0, "./assets/hero.bmp");

    struct Sprite fires[20];
    for (size_t i = 0; i < 20; i++)
    {
        fires[i] = make_sprite(renderer, 0, 0, 4, 10, 4, 1, "./assets/fire.bmp");
    }

    struct Sprite enemys[20];
    for (size_t i = 0; i < 20; i++)
    {
        enemys[i] = make_sprite(renderer, 0, 0, 34, 44, 1, 1, "./assets/enemy.bmp");
    }

    int score = 0;
    TTF_Font *score_font = TTF_OpenFont("./assets/font.ttf", 40);
    TTF_Font *title_font = TTF_OpenFont("./assets/font.ttf", 70);
    TTF_Font *info_font = TTF_OpenFont("./assets/font.ttf", 20);
    if (!score_font)
    {
        printf("Font_Load: %s\n", TTF_GetError());
    }

    while (!quit)
    {
        if (game_status == 0)
        {
            SDL_Color color = {255, 0, 0};
            draw_text_center(renderer, title_font, color, "AirWar", WINDOW_WIDTH, WINDOW_HEIGHT, 0, -20);
            draw_text_center(renderer, info_font, color, "press space to start", WINDOW_WIDTH, WINDOW_HEIGHT, 0, 30);
            while (SDL_PollEvent(&event) > 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_SPACE:
                        game_status = 1;
                        break;
                    }
                }
            }
        }
        if (game_status == 3)
        {
            SDL_Color color = {255, 0, 0};
            draw_text_center(renderer, title_font, color, "GAME OVER", WINDOW_WIDTH, WINDOW_HEIGHT, 0, -20);
            draw_text_center(renderer, info_font, color, "press R to restart", WINDOW_WIDTH, WINDOW_HEIGHT, 0, 30);
            while (SDL_PollEvent(&event) > 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_R:
                        for (size_t i = 0; i < 20; i++)
                        {
                            enemys[i].die = 1;
                            fires[i].die = 1;
                        }
                        score = 0;
                        game_status = 1;
                        hero.vx = 0;
                        hero.vy = 0;
                        break;
                    }
                }
            }
        }
        if (game_status == 1)
        {
            while (SDL_PollEvent(&event) > 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                // 使用 if else 能确保 按下时和抬起时是2个判断。如果用switch，则抬起后，按下的逻辑就被覆盖了。原因是switch A的条件如果变为B满足，则会执行B。而if else 当A的条件设为B满足后，会在下一次才能执行B。
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_W:
                        hero.vy = -1;
                        hero.vx = 0;
                        break;
                    case SDL_SCANCODE_S:
                        hero.vy = 1;
                        hero.vx = 0;
                        break;
                    case SDL_SCANCODE_A:
                        hero.vx = -1;
                        hero.vy = 0;
                        break;
                    case SDL_SCANCODE_D:
                        hero.vx = 1;
                        hero.vy = 0;
                        break;
                    }
                }
                else if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_W:
                        hero.vy = 0;
                        break;
                    case SDL_SCANCODE_S:
                        hero.vy = 0;
                        break;
                    case SDL_SCANCODE_A:
                        hero.vx = 0;
                        break;
                    case SDL_SCANCODE_D:
                        hero.vx = 0;
                        break;
                    case SDL_SCANCODE_J:
                        for (size_t i = 0; i < 20; i++)
                        {
                            if (fires[i].die == 1)
                            {
                                fires[i].x = (int)(hero.x + hero.w / 2 - fires[i].w / 4);
                                fires[i].y = hero.y;
                                fires[i].die = 0;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            // SDL_WaitEvent(&event);//这里会卡住，导致必须有按键输入才能继续，所以注释掉了，采用while (SDL_PollEvent(&event) > 0)的方法可以避免卡住
            loop_time += 1;
            SDL_RenderClear(renderer);

            if (loop_time % 60 == 0)
            {
                for (size_t i = 0; i < 20; i++)
                {
                    if (enemys[i].die == 1)
                    {
                        time_t t;
                        srand((unsigned)time(&t));
                        enemys[i].x = rand() % WINDOW_WIDTH;
                        enemys[i].y = -1 * enemys[i].h;
                        enemys[i].die = 0;
                        break;
                    }
                }
            }

            hero.x += hero.vx * hero.speed;
            hero.y += hero.vy * hero.speed;

            stay_on_screen(&hero, WINDOW_WIDTH, WINDOW_HEIGHT);

            // update and draw fire
            for (size_t i = 0; i < 20; i++)
            {
                if (fires[i].die == 0)
                {
                    fires[i].y -= fires[i].speed;
                    draw_sprite(renderer, fires[i]);
                }
            }
            for (size_t i = 0; i < 20; i++)
            {
                if (fires[i].y <= -1 * fires[i].h)
                {
                    fires[i].die = 1;
                }
            }

            // update and draw enemy
            for (size_t i = 0; i < 20; i++)
            {
                if (enemys[i].die == 0)
                {
                    enemys[i].y += enemys[i].speed;
                    if (enemys[i].y > WINDOW_HEIGHT)
                    {
                        enemys[i].die = 1;
                    }
                    else
                    {
                        if (check(enemys[i], hero))
                        {
                            game_status = 3;
                        }
                    }
                    draw_sprite(renderer, enemys[i]);
                }
            }

            // check
            for (size_t i = 0; i < 20; i++)
            {
                for (size_t j = 0; j < 20; j++)
                {
                    if (enemys[i].die == 0 && fires[j].die == 0)
                    {
                        if (check(enemys[i], fires[j]))
                        {
                            enemys[i].die = 1;
                            fires[j].die = 1;
                            score += 1;
                        }
                    }
                }
            }

            draw_sprite(renderer, hero);
            // draw_sprite(renderer, gameover);

            draw_score(renderer, score_font, score);
        }

        SDL_RenderPresent(renderer);
        // SDL_UpdateWindowSurface(screen);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(hero.texture);
    SDL_FreeSurface(hero.surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

    IMG_Quit();
    SDL_Quit();

    TTF_CloseFont(score_font);
    TTF_CloseFont(title_font);
    TTF_CloseFont(info_font);
    TTF_Quit();
    return 0;
}
