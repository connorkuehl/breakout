#ifndef BREAKOUT_BALL_H_
#define BREAKOUT_BALL_H_

#include <SDL_render.h>

#include "collision.h"

#define BALL_SPEED 200.f

struct ball {
    float x;
    float y;
    int dx;
    int dy;
    int w;
    int h;
    struct collisions collisions;
};

void ball_spawn(struct ball *ball);
void ball_update(struct ball *ball, float dt);
void ball_draw(struct ball *ball, SDL_Renderer *renderer);

#endif

