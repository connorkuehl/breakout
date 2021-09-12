#include <SDL_render.h>

#include "paddle.h"

float const PADDLE_SPEED = 250.f;

void paddle_update(struct paddle *paddle, float dt)
{
    int x_dir = 0;
    switch (paddle->direction) {
        case PADDLE_DIRECTION_LEFT:
            x_dir = -1;
            break;
        case PADDLE_DIRECTION_RIGHT:
            x_dir = 1;
            break;
        default:
            x_dir = 0;
            break;
    }
    paddle->x += (PADDLE_SPEED * x_dir * dt);
}

void paddle_draw(struct paddle *paddle, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect rect = {
        .w = paddle->w,
        .h = paddle->h,
        .x = paddle->x,
        .y = paddle->y,
    };
    SDL_RenderFillRect(renderer, &rect);
}

