#include "breakout.h"

#include "ball.h"

void ball_spawn(struct ball *ball)
{
    float margins = BREAKOUT_GAME_WIDTH * 0.13f;
    int horizontal_spawn_space = BREAKOUT_GAME_WIDTH - margins;

    ball->x = rand() % horizontal_spawn_space;
    if (ball->x < margins) {
        ball->x += margins;
    }

    ball->y = BREAKOUT_GAME_HEIGHT * 0.30f;

    ball->dy = 1;
    ball->dx = rand() % 2 == 0 ? 1 : -1;
}

void ball_update(struct ball *ball, float dt)
{
    for (int i = 0; i < ball->collisions.size; ++i) {
        enum colliding_with with = ball->collisions.collisions[i];
        switch (with) {
        case COLLIDING_WITH_PADDLE:
        case COLLIDING_WITH_BRICK:
        case COLLIDING_WITH_TOP_WALL:
            ball->dy *= -1;
            break;
        case COLLIDING_WITH_SIDE_WALL:
            ball->dx *= -1;
            break;
        default:
            break;
        }
        collisions_remove(&ball->collisions, i);
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

