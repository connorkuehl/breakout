#include "breakout.h"

#include "ball.h"

float const BALL_SPEED = 200.f;

void ball_update(struct ball *ball, float dt)
{
    float epsilon = 3.f;

    if (ball->x - epsilon <= 0.f || ball->x + ball->w + epsilon >= BREAKOUT_GAME_WIDTH) {
        ball->dx *= -1;
    }
    if (ball->y - epsilon <= 0.f) {
        ball->dy *= -1;
    }

    ball->x += (BALL_SPEED * ball->dx * dt);
    //ball->y += (BALL_SPEED * ball->dy * dt);
}

void ball_draw(struct ball *ball, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect rect = {
        .w = ball->w,
        .h = ball->h,
        .x = ball->x,
        .y = ball->y,
    };
    SDL_RenderFillRect(renderer, &rect);
}

