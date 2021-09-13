#include <assert.h>
#include <time.h>

#include "collision.h"

#include "breakout.h"

static void collision_system(struct breakout *breakout, float dt);

void breakout_reset(struct breakout *breakout)
{
    free(breakout->bricks);
    breakout->bricks = NULL;

    breakout->lives = LIVES;
    breakout->score = 0;

    struct paddle *player = &breakout->player;
    player->w = 96;
    player->h = 16;
    player->x = (BREAKOUT_GAME_WIDTH / 2) - (player->w / 2);
    player->y = BREAKOUT_GAME_HEIGHT - (player->h + 16);
    player->direction = PADDLE_DIRECTION_NONE;

    srand(time(0));

    struct ball *ball = &breakout->ball;
    ball->w = 8;
    ball->h = 8;
    ball_spawn(ball);

    int n_cols = BREAKOUT_GAME_WIDTH / (BRICK_WIDTH + BRICK_GAP);
    int n_rows = (BREAKOUT_GAME_HEIGHT * 0.25) / (BRICK_HEIGHT + BRICK_GAP);
    int n_bricks = n_cols * n_rows;
    breakout->n_bricks = n_bricks;
    assert(breakout->n_bricks > 0);

    // TODO: need to be able to fail here
    breakout->bricks = calloc(n_bricks, sizeof(breakout->bricks[0]));
    assert(breakout->bricks);

    int y_offset = 24;
    int x_offset = 12;

    int y_gap = 0;
    int x_gap = 0;
    for (int row = 0; row < n_rows; ++row) {
        for (int col = 0; col < n_cols; ++col) {
            float x = col * (BRICK_WIDTH + x_gap) + x_offset;
            float y = row * (BRICK_HEIGHT + y_gap) + y_offset;

            breakout->bricks[(row * n_cols) + col] = (struct brick) {
                .w = BRICK_WIDTH,
                .h = BRICK_HEIGHT,
                .x = x,
                .y = y,
                .health = BRICK_HEALTH,
            };
            x_gap = BRICK_GAP;
        }
        y_gap = BRICK_GAP;
    }
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

    struct ball *ball = &breakout->ball;
    if (ball->y + (ball->h / 2) >= BREAKOUT_GAME_HEIGHT) {
        --breakout->lives;
        ball_spawn(ball);
        if (breakout->lives < 1) {
            breakout_reset(breakout);
        }
    }

    for (int i = 0; i < breakout->n_bricks; ++i) {
        struct brick *brick = &breakout->bricks[i];

        brick_update(brick, dt);

        if (brick->health < 1) {
            --breakout->n_bricks;
            *brick = breakout->bricks[breakout->n_bricks];
            breakout->score += POINTS_PER_BRICK;
        }
    }

    collision_system(breakout, dt);
}

void breakout_draw(struct breakout *breakout, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x9, 0x1f, 0x92, 0xff);
    SDL_RenderClear(renderer);

    for (int i = 0; i < breakout->n_bricks; ++i) {
        brick_draw(&breakout->bricks[i], renderer);
    }

    paddle_draw(&breakout->player, renderer);
    ball_draw(&breakout->ball, renderer);

    char lives[32] = {};
    snprintf(lives, sizeof(lives), "lives: %d", breakout->lives);
    SDL_Surface *lives_surface = TTF_RenderText_Solid(breakout->assets.font, lives, ((SDL_Color) { 0xff, 0xff, 0xff, 0xff }));
    if (!lives_surface) {
        fprintf(stderr, "TTF_RenderText_Solid: %s\n", TTF_GetError());
        goto done;
    }

    SDL_Texture *lives_tex = SDL_CreateTextureFromSurface(renderer, lives_surface);
    if (!lives_tex) {
        SDL_FreeSurface(lives_surface);
        fprintf(stderr, "SDL_CreateTextureFromSurface: %s\n", TTF_GetError());
        goto done;
    }

    SDL_Rect lives_rect = {
        .w = lives_surface->w,
        .h = lives_surface->h,
        .x = BREAKOUT_GAME_WIDTH - lives_surface->w - 15,
        .y = 5,
    };
    SDL_FreeSurface(lives_surface);

    SDL_RenderCopy(renderer, lives_tex, NULL, &lives_rect);
    SDL_DestroyTexture(lives_tex);

    char score[32] = {};
    snprintf(score, sizeof(score), "score: %d", breakout->score);
    SDL_Surface *score_surface = TTF_RenderText_Solid(breakout->assets.font, score, ((SDL_Color) { 0xff, 0xff, 0xff, 0xff }));
    if (!score_surface) {
        fprintf(stderr, "TTF_RenderText_Solid: %s\n", TTF_GetError());
        goto done;
    }

    SDL_Texture *score_tex = SDL_CreateTextureFromSurface(renderer, score_surface);
    if (!score_tex) {
        SDL_FreeSurface(score_surface);
        fprintf(stderr, "SDL_CreateTextureFromSurface: %s\n", TTF_GetError());
        goto done;
    }

    SDL_Rect score_rect = {
        .w = score_surface->w,
        .h = score_surface->h,
        .x = (BREAKOUT_GAME_WIDTH / 2) - (score_surface->w / 2),
        .y = 5,
    };
    SDL_FreeSurface(score_surface);

    SDL_RenderCopy(renderer, score_tex, NULL, &score_rect);
    SDL_DestroyTexture(score_tex);


done:
    return;
}

void breakout_cleanup(struct breakout *breakout)
{
    free(breakout->bricks);
    breakout->bricks = NULL;
    breakout->n_bricks = 0;
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
        collisions_add(&ball->collisions, COLLIDING_WITH_PADDLE);
    }
}

static void ball_and_bricks(struct breakout *breakout, float dt)
{
    struct ball *ball = &breakout->ball;
    SDL_Rect b = {
        .w = ball->w,
        .h = ball->h,
        .x = ball->x + (ball->dx * 3.f * dt),
        .y = ball->y + (ball->dy * 3.f * dt),
    };

    for (int i = 0; i < breakout->n_bricks; ++i) {
        struct brick *brick = &breakout->bricks[i];
        SDL_Rect brk = {
            .w = brick->w,
            .h = brick->h,
            .x = brick->x,
            .y = brick->y,
        };

        if (SDL_HasIntersection(&b, &brk)) {
            collisions_add(&brick->collisions, COLLIDING_WITH_BALL);
            collisions_add(&ball->collisions, COLLIDING_WITH_BRICK);
        }
    }
}

static void collision_system(struct breakout *breakout, float dt)
{
    ball_and_player(&breakout->player, &breakout->ball, dt);
    ball_and_bricks(breakout, dt);
}
