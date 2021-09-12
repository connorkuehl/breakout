#include "breakout.h"

#include "ball.h"

float const BALL_SPEED = 200.f;

void ball_spawn(struct ball *ball)
{
    float margins = BREAKOUT_GAME_WIDTH * 0.13f;
    int horizontal_spawn_space = BREAKOUT_GAME_WIDTH - margins;

    ball->x = rand() % horizontal_spawn_space;
    if (ball->x < margins) {
        ball->x += margins;
    }

    ball->y = BREAKOUT_GAME_HEIGHT * 0.5f;

    ball->dy = 1;
    ball->dx = rand() % 2 == 0 ? 1 : -1;
}

void ball_update(struct ball *ball, float dt)
{
    float epsilon = 3.f * dt;

    if (ball->x - epsilon <= 0.f || ball->x + ball->w + epsilon >= BREAKOUT_GAME_WIDTH) {
        ball->dx *= -1;
    }
    if (ball->y - epsilon <= 0.f) {
        ball->dy *= -1;
    }

    ball->x += (BALL_SPEED * ball->dx * dt);
    ball->y += (BALL_SPEED * ball->dy * dt);
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

