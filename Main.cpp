#include "Functions.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "Globals.h"
#include "Classes.h"
#include <ctime>
#include <cstdlib>

int main ( int argc, char * args[] )
{
	if ( init() == false )
	{
		return 1;
	}
	currentState = new Menu();

	curState = MENU;

	int FPS = NULL;

	srand(time(NULL));

	t_numbers[0] =  load_texture("0.png");
	t_numbers[1] =  load_texture("1.png");
	t_numbers[2] =  load_texture("2.png");
	t_numbers[3] =  load_texture("3.png");
	t_numbers[4] =  load_texture("4.png");
	t_numbers[5] =  load_texture("5.png");
	t_numbers[6] =  load_texture("6.png");
	t_numbers[7] =  load_texture("7.png");
	t_numbers[8] =  load_texture("8.png");
	t_numbers[9] =  load_texture("9.png");

	menu = load_texture("menu.png");

	for ( int n = 0; n < 0; n++ )
	{
		SCORE[n]=0;}

	music = Mix_LoadMUS( "BigBlue.mid" );
	Mix_PlayMusic( music, -1);


	while(nextState != EXIT)
	{
		FPS = SDL_GetTicks();

		///////////////////EVENT////////////////////

		currentState->handle_input();
		////////////////////////////////////////////


		///////////////////LOGIC////////////////////

		currentState->logic();

		///////////////////////////////////////////

		//////////////////RENDER////////////////////
		glClear(GL_COLOR_BUFFER_BIT);

		currentState->render();

		SDL_GL_SwapBuffers();

		change_state();


		////////////////////////////////////////////


		if ( (SDL_GetTicks() - FPS) < 1000/60 )
		{
			SDL_Delay( ( 1000/60) - (SDL_GetTicks() - FPS) );
		}
	}

	return 0;
}