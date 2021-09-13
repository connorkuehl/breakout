#ifndef BREAKOUT_BRICK_H_
#define BREAKOUT_BRICK_H_

#include <SDL_render.h>

#define BRICK_WIDTH  46
#define BRICK_HEIGHT 12
#define BRICK_GAP    5
#define BRICK_HEALTH 3

struct brick {
    float x;
    float y;
    float w;
    float h;
    int health;
};

void brick_draw(struct brick *brick, SDL_Renderer *renderer);

#endif

