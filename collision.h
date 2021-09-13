#ifndef BREAKOUT_COLLISION_H_
#define BREAKOUT_COLLISION_H_

#define MAX_COLLISION 4

enum colliding_with {
    COLLIDING_WITH_BALL,
    COLLIDING_WITH_PADDLE,
    COLLIDING_WITH_BRICK,
};

struct collisions {
    enum colliding_with collisions[MAX_COLLISION];
    int size;
};

void collisions_add(struct collisions *collisions, enum colliding_with with);
void collisions_remove(struct collisions *collisions, int idx);

#endif
