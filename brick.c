#include "brick.h"

void brick_draw(struct brick *brick, struct SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect rect = {
        .w = brick->w,
        .h = brick->h,
        .x = brick->x,
        .y = brick->y,
    };
    SDL_RenderFillRect(renderer, &rect);
}

