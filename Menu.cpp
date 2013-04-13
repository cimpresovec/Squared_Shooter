#include "Classes.h"
#include "Globals.h"
#include "Functions.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>


Menu::Menu()
{


}


void Menu::handle_input()
{
	if ( SDL_PollEvent(&event) )
	{
		if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
		{
			set_state(EXIT);
		}

		else if ( event.type == SDL_KEYUP )
		{
			set_state(GAME);

			for ( int n = 0; n < 10; n++ )
			{
				SCORE[n] = 0;
			}
		}
	}

}

void Menu::logic()
{

}

void Menu::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	

	glPushMatrix();
	
		gluOrtho2D(0,800,600,0);
		

		glEnable(GL_TEXTURE_2D);
	

		glColor4d(1,1,1,1);
		glBindTexture(GL_TEXTURE_2D, menu );

			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,0);
				glTexCoord2f(1,0); glVertex2f(800,0);
				glTexCoord2f(1,1); glVertex2f(800,600);
				glTexCoord2f(0,1); glVertex2f(0,600);
			glEnd();

			glColor4d(0,1,0,1);

			for ( int g = 0, x = 640; g < 10; g++, x+= 15 )
		{
			int n = SCORE[g];		

			glBindTexture(GL_TEXTURE_2D, t_numbers[n]);

			glBegin(GL_QUADS);

				glTexCoord2f(0,0); glVertex2f(x,550);
				glTexCoord2f(1,0); glVertex2f(x+13,550);
				glTexCoord2f(1,1); glVertex2f(x+13, 590);
				glTexCoord2f(0,1); glVertex2f(x,590);
			glEnd();
		}

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
		
