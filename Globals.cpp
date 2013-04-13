#include "Globals.h"
#include "Classes.h"

#include <SDL.h>
#include <SDL_mixer.h>

SDL_Event event;

gameState curState = NUL;
gameState nextState = NUL;

GameState * currentState = NULL;

float MOUSE_ANGLE = 0;

unsigned t_numbers[10];
unsigned menu;

Box numbers[10];

int SCORE[10];

Mix_Music * music;