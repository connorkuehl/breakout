#include "breakout.h"

char *const BREAKOUT_GAME_TITLE = "breakout";
int const BREAKOUT_GAME_WIDTH   = 640;
int const BREAKOUT_GAME_HEIGHT  = 480;

void breakout_reset(struct breakout *breakout)
{
    struct paddle *player = &breakout->player;
    player->w = 128;
    player->h = 16;
    player->x = (BREAKOUT_GAME_WIDTH / 2) - (player->w / 2);
    player->y = BREAKOUT_GAME_HEIGHT - (player->h + 16);
    player->direction = PADDLE_DIRECTION_NONE;
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
}

void breakout_draw(struct breakout *breakout, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x9, 0x1f, 0x92, 0xff);
    SDL_RenderClear(renderer);

    paddle_draw(&breakout->player, renderer);
}
