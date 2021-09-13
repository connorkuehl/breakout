#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "breakout.h"

double const S_PER_FRAME = 1.0 / 60.0;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        goto sdl_quit;
    }

    SDL_Window *window = SDL_CreateWindow(
            BREAKOUT_GAME_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            BREAKOUT_GAME_WIDTH,
            BREAKOUT_GAME_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        goto ttf_quit;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        goto free_window;
    }

    SDL_SetRenderDrawColor(renderer, 0x9, 0x1f, 0x92, 0xff);

    TTF_Font *font = TTF_OpenFont("./res/font/press_start_2p.ttf", 16);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        goto free_renderer;
    }

    struct breakout game = {};
    breakout_reset(&game);

    bool should_quit = false;

    double last_time = (double)SDL_GetPerformanceCounter();
    double accumulator = 0.0;

    while (!should_quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                should_quit = true;
            }

            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) {
                should_quit = true;
            }

            breakout_handle_input(&game, e);
        }

        double now = (double)SDL_GetPerformanceCounter();
        double frame_time = (now - last_time) / SDL_GetPerformanceFrequency();
        last_time = now;

        accumulator += frame_time;

        while (accumulator >= S_PER_FRAME) {
            breakout_update(&game, S_PER_FRAME);
            accumulator -= S_PER_FRAME;
        }

        SDL_RenderClear(renderer);

        breakout_draw(&game, renderer);

        char fps[32] = {};
        sprintf(fps, "%.2f", 1.0 / frame_time);
        SDL_Surface *fps_surface = TTF_RenderText_Solid(font, fps, ((SDL_Color) { 0xff, 0xff, 0xff, 0xff }));
        if (!fps_surface) {
            fprintf(stderr, "TTF_RenderTextSolid: %s\n", TTF_GetError());
            goto free_renderer;
        }

        SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
        if (!fps_texture) {
            SDL_FreeSurface(fps_surface);
            fprintf(stderr, "SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
            goto free_renderer;
        }
        SDL_FreeSurface(fps_surface);

        SDL_Rect font_rect = {
            .w = fps_surface->w,
            .h = fps_surface->h,
            .x = 8,
            .y = 8,
        };

        SDL_RenderCopy(renderer, fps_texture, NULL, &font_rect);
        SDL_DestroyTexture(fps_texture);

        SDL_RenderPresent(renderer);
    }

    breakout_cleanup(&game);

free_renderer:
    SDL_DestroyRenderer(renderer);

free_window:
    SDL_DestroyWindow(window);

ttf_quit:
    TTF_Quit();

sdl_quit:
    SDL_Quit();
    return 0;
}
