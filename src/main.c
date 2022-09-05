#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

/**
 * Initial defines
 */

#define WIDTH 1024
#define HEIGHT 768

#define WALK_RATE 10

#define max(a, b) (a > b ? a : b);
#define min(a, b) (a < b ? a : b);
#define equals(a, b) (a == b);


/**
 * Structs
 */

typedef struct {

    int x;
    int y;

    float life;
    float maxLife;

    int alive; // ta vivo = 1, ta morto = 0

} CHARACTER ;

/**
 * Character
 */

void moveCharacter(CHARACTER*, int x, int y);
int damageCharacter(CHARACTER*, float); // 0 died | 1 alive

/**
 * Image rendering
 */

void render(SDL_Renderer*, int);
void renderGame(SDL_Renderer*);

int main(int argc, char const *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
    
    SDL_Window *win = SDL_CreateWindow("GAME", 100, 100, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    int state = 0;

    while(1) {
        render(renderer, state);
    }

    SDL_DestroyWindow(win);
    return 0;
}

void render(SDL_Renderer* renderer, int state) {
    switch(state) {
    case 2: {
        renderGame(renderer);
        // rende the game
        break;
    }
    case 1: {
        // select your champion
        break;
    }
    default: {
        //menu
        break;
    }
    }
}

void renderGame(SDL_Renderer* renderer) {
	SDL_Event e;
    CHARACTER character; // nada a ver isso auqi

	if(SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w)
			moveCharacter(&character, 0, -1);
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
			moveCharacter(&character, 0, 1);
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_a)
			moveCharacter(&character, -1, 0);
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_d)
			moveCharacter(&character, 0, 1);
    } 

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void moveCharacter(CHARACTER* character, int x, int y) {
    character->x = character->x + (x * WALK_RATE);
    character->y = character->y + (y * WALK_RATE);
}

int damageCharacter(CHARACTER* character, float life) {
    if (character->life - life <= 0) {
        character->life = 0;
        character->alive = 0;
        return 0;
    }

    character->life = character->life - life;
    return 1;
}