#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Classes.h"
#include "Globals.h"
#include <string>
#include <SDL_opengl.h>

bool init();

float calc_speed( float angle, float xSpeed, int mode );

float calc_angle( Box A, Box B );

bool check_collision_rotated( Rect A, Rect B );

void set_state(gameState nextsState);

void change_state();

GLuint load_texture( std::string file );

#endif