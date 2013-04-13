#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "Classes.h"

extern SDL_Event event;

enum gameState { 
	NUL, EXIT, GAME, MENU }; 

extern gameState curState;
extern gameState nextState;

extern GameState * currentState;

extern float MOUSE_ANGLE;

extern unsigned t_numbers[10];
extern unsigned menu;

extern Box numbers[10];

extern int SCORE[10];

extern Mix_Music * music;


#endif