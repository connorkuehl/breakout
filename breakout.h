#ifndef BREAKOUT_BREAKOUT_H_
#define BREAKOUT_BREAKOUT_H_

#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_ttf.h>


#include "ball.h"
#include "brick.h"
#include "paddle.h"

#define LIVES 3
#define POINTS_PER_BRICK 10

extern char *const BREAKOUT_GAME_TITLE;
extern int const BREAKOUT_GAME_WIDTH;
extern int const BREAKOUT_GAME_HEIGHT;

struct breakout {
    struct paddle player;
    struct ball ball;
    struct brick *bricks;
    int n_bricks;
    int lives;
    int score;

    struct {
        TTF_Font *font;
    } assets;
};

void breakout_cleanup(struct breakout *breakout);
void breakout_reset(struct breakout *breakout);
void breakout_handle_input(struct breakout *breakout, SDL_Event event);
void breakout_update(struct breakout *breakout, float dt);
void breakout_draw(struct breakout *breakout, SDL_Renderer *renderer);

#endif

