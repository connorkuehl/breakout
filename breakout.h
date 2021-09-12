#ifndef BREAKOUT_BREAKOUT_H_
#define BREAKOUT_BREAKOUT_H_

#include <SDL_events.h>
#include <SDL_render.h>

#include "ball.h"
#include "paddle.h"

extern char *const BREAKOUT_GAME_TITLE;
extern int const BREAKOUT_GAME_WIDTH;
extern int const BREAKOUT_GAME_HEIGHT;

struct breakout {
    struct paddle player;
    struct ball ball;
};

void breakout_reset(struct breakout *breakout);
void breakout_handle_input(struct breakout *breakout, SDL_Event event);
void breakout_update(struct breakout *breakout, float dt);
void breakout_draw(struct breakout *breakout, SDL_Renderer *renderer);

#endif

