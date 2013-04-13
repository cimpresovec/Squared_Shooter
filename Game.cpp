#include "Classes.h"
#include "Globals.h"
#include "Functions.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>

Game::Game()
{
	i_enemiesLevel = 50;

	for ( int n = 0; n < 0; n++ )
	{
		SCORE[n]=0;}
}

void Game::handle_input()
{
	if ( SDL_PollEvent(&event) )
	{
		if ( event.type == SDL_KEYUP )
		{
			if ( event.key.keysym.sym == SDLK_ESCAPE ){
				set_state(MENU);}
		}

		o_player.handle_input();
	}

}

void Game::logic()
{
	o_player.logic_input();
	o_player.move();
	o_player.shot( o_bulets, o_particles );
	o_player.check_collision(o_bulets, o_enemies);

	for ( int n = 0; n < (signed)o_bulets.size(); n++ )
	{
		o_bulets[n]->move();
	}

	MOUSE_ANGLE = calc_angle(o_player.get_box(),o_player.get_mouse());
	float angle = MOUSE_ANGLE;
	bool right = true;
	for ( int n = 0; n < (signed)o_particles.size(); n++ )
	{
		o_particles[n]->move(&o_player);	
		if ( right == true )
		{
			if ( MOUSE_ANGLE++ > angle + (o_particles.size() / 2 ) )
			{
				right = false;
				MOUSE_ANGLE = angle;
			}
		}
		else {
			MOUSE_ANGLE--;}

	}

	if ( rand() % 50 == 10 )
	{
		o_enemies.push_back( new Enemy( i_enemiesLevel ) ); 
	}

	for ( int n = 0; n < ( signed ) o_enemies.size(); n++ )
	{
		o_enemies[n]->move(o_player);
		o_enemies[n]->check_collision(o_bulets, o_particles);
	}

	for ( int n = 0; n < ( signed ) o_enemies.size(); n++ )
	{
		if ( o_enemies[n]->b_die == true )
		{
			o_enemies.erase(o_enemies.begin()+n);
		}
	}

	for ( int n = 0; n < (signed)o_bulets.size(); n++ )
	{
		if ( o_bulets[n]->b_die == true )
		{
			o_bulets.erase(o_bulets.begin()+n);
		}
	}

	for ( int n = 0; n < (signed)o_particles.size(); n++ )
	{
		if ( o_particles[n]->b_die == true )
		{
			o_particles.erase(o_particles.begin()+n);
		}
	}

	i_enemiesLevel+=(float)0.05;
	if ( i_enemiesLevel > 660 )
	{
		i_enemiesLevel = 660;
	}

}

void Game::render()
{

	glClear(GL_COLOR_BUFFER_BIT);

	/*glPushMatrix();
			{
				gluOrtho2D(0,800,600,0);
				glEnable(GL_TEXTURE_2D);
				
				glBindTexture(GL_TEXTURE_2D, t_numbers);

				glColor4d(1,1,1,1);

				glBegin(GL_QUADS);
				{
					glTexCoord2i(0,0); glVertex2f(0,0);
					glTexCoord2i(1,0); glVertex2f(100,0);
					glTexCoord2i(1,1); glVertex2f(100,100);
					glTexCoord2i(0,1); glVertex2f(0,100);

				}
				glEnd();
				glDisable(GL_TEXTURE_2D);

			}
	glPopMatrix();*/
	
	o_player.render();

	for ( int n = 0; n < (signed)o_bulets.size(); n++ )
	{
		o_bulets[n]->show();
	}

	for ( int e = 0; e < (signed)o_enemies.size(); e++ )
	{
		o_enemies[e]->show();
	}

	for ( int n = 0; n < (signed)o_particles.size(); n++ )
	{
		o_particles[n]->show();
	}
}

void GameState::handle_input()
{

}

void GameState::logic()
{

}

void GameState::render()
{

}