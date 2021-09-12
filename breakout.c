#include "breakout.h"

char *const BREAKOUT_GAME_TITLE = "breakout";
int const BREAKOUT_GAME_WIDTH   = 640;
int const BREAKOUT_GAME_HEIGHT  = 480;

static void collision_system(struct breakout *breakout, float dt);

void breakout_reset(struct breakout *breakout)
{
    struct paddle *player = &breakout->player;
    player->w = 128;
    player->h = 16;
    player->x = (BREAKOUT_GAME_WIDTH / 2) - (player->w / 2);
    player->y = BREAKOUT_GAME_HEIGHT - (player->h + 16);
    player->direction = PADDLE_DIRECTION_NONE;

    struct ball *ball = &breakout->ball;
    ball->w = 16;
    ball->h = 16;
    ball->x = (BREAKOUT_GAME_WIDTH / 2) - (ball->w / 2);
    ball->y = BREAKOUT_GAME_HEIGHT - ball->h - 64;
    ball->dy = -1;
}

void breakout_handle_input(struct breakout *breakout, SDL_Event event)
{
    struct paddle *player = &breakout->player;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                player->direction = PADDLE_DIRECTION_LEFT;
                break;
            case SDLK_RIGHT:
                player->direction = PADDLE_DIRECTION_RIGHT;
                break;
        }
    }
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_RIGHT:
                player->direction = PADDLE_DIRECTION_NONE;
                break;
        }
    }
}

void breakout_update(struct breakout *breakout, float dt)
{
    paddle_update(&breakout->player, dt);
    ball_update(&breakout->ball, dt);

    collision_system(breakout, dt);
}

void breakout_draw(struct breakout *breakout, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x9, 0x1f, 0x92, 0xff);
    SDL_RenderClear(renderer);

    paddle_draw(&breakout->player, renderer);
    ball_draw(&breakout->ball, renderer);
}

static void ball_and_player(struct paddle *player, struct ball *ball, float dt)
{
    SDL_Rect b = {
        .w = ball->w,
        .h = ball->h,
        .x = ball->x + (ball->dx * 3.f * dt),
        .y = ball->y + (ball->dy * 3.f * dt),
    };

    SDL_Rect p = {
        .w = player->w,
        .h = player->h,
        .x = player->x,
        .y = player->y,
    };

    if (SDL_HasIntersection(&b, &p)) {
        ball->dx *= -1;
        ball->dy *= -1;
    }
}

static void collision_system(struct breakout *breakout, float dt)
{
    ball_and_player(&breakout->player, &breakout->ball, dt);
}
