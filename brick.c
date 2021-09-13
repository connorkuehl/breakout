#include "brick.h"

static SDL_Color const GREEN = (const SDL_Color) { .a = 0xff, .g = 0xff };
static SDL_Color const YELLOW = (const SDL_Color) { .a = 0xff, .r =0xff, .g = 0xff };
static SDL_Color const RED = (const SDL_Color) { .a = 0xff, .r =0xff };

static SDL_Color const health_colors[BRICK_HEALTH] = {
    RED,
    YELLOW,
    GREEN,
};

void brick_draw(struct brick *brick, struct SDL_Renderer *renderer)
{
    SDL_Color const *color = &health_colors[(brick->health - 1) % BRICK_HEALTH];
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_Rect rect = {
        .w = brick->w,
        .h = brick->h,
        .x = brick->x,
        .y = brick->y,
    };
    SDL_RenderFillRect(renderer, &rect);
}

