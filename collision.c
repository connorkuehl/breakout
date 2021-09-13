#include "collision.h"

void collisions_add(struct collisions *collisions, enum colliding_with with)
{
    if (collisions->size >= MAX_COLLISION) {
        return;
    }
    collisions->collisions[collisions->size++] = with;
}

void collisions_remove(struct collisions *collisions, int idx)
{
    if (idx >= collisions->size || idx < 0) {
        return;
    }
    --collisions->size;
    collisions->collisions[idx] = collisions->collisions[collisions->size];
}

