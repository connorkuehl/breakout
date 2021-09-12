#ifndef BREAKOUT_BALL_H_
#define BREAKOUT_BALL_H_

#include <SDL_render.h>

extern float const BALL_SPEED;

struct ball {
    float x;
    float y;
    int dx;
    int dy;
    int w;
    int h;
};

void ball_update(struct ball *ball, float dt);
void ball_draw(struct ball *ball, SDL_Renderer *renderer);

#endif

