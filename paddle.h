#ifndef BREAKOUT_PADDLE_H_
#define BREAKOUT_PADDLE_H_

#include <SDL_render.h>

extern float const PADDLE_SPEED;

enum paddle_direction {
    PADDLE_DIRECTION_NONE,
    PADDLE_DIRECTION_LEFT,
    PADDLE_DIRECTION_RIGHT,
};

struct paddle {
    int x;
    int y;
    int w;
    int h;
    enum paddle_direction direction;
};

void paddle_update(struct paddle *paddle, float dt);
void paddle_draw(struct paddle *paddle, SDL_Renderer *renderer);

#endif

