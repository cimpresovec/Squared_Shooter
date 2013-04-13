#include "Classes.h"
#include "Functions.h"
#include <SDL_opengl.h>
#include <iostream>
#include <cstdlib>

Enemy::Enemy( int level )
{
	switch ( rand() % 4 )
	{
	case 0: box.x = rand() % 800; box.y = -200; break;
	case 1: box.x = rand() % 800; box.y = 800; break;
	case 2: box.y = rand() % 600; box.x = 1000; break;
	case 3: box.y = rand() % 600; box.x = -200; break;
	}

	size = (rand() % level) + 1;
	level -= size;

	box.w = (rand() % size) + 20;
	box.h = (rand() % (int)((size + 1) - (box.w - 20))) + 20;

	i_xVel = 0;
	i_yVel = 0;
		
	i_speed = level/size;

	if ( i_speed < 0.8 ) { i_speed = 0.8; }
	if ( i_speed > 3.5 ) { i_speed = 3.5; }

	//////

	i_angle = 0;
	b_die = false;

	rect.set(box, i_angle);
}

Rect Enemy::get_rect()
{
	return rect;}

void Enemy::check_collision( std::vector<Bulet*> &bulets, std::vector<Particle*> &particle )
{
	for ( int n = 0; n < (signed)bulets.size(); n++ )
	{
		if ( bulets[n]->b_enemy == false ){
		if ( check_collision_rotated(rect, bulets[n]->get_rect()) == true )
		{
			//box.x++;
			//box.y++;
			box.w--;
			box.h--;
			if ( box.w < 15 || box.h < 15 ) 
			{
				b_die = true; 
				
			}

			SCORE[9]++; 
			for ( int g = 9; g >= 0; g-- ) 
				{ 
					if ( SCORE[g] == 10 ) 
					{ 
						SCORE[g-1]++; SCORE[g] = 0; 
					}  
				}
			
			size--;

			/*if ( size <= 0 )
			{
				b_die = true;
			}*/

			bulets[n]->b_die = true; 

			rect.set(box,i_angle);

			particle.push_back(new Particle(bulets[n]->get_rect().UR.x, bulets[n]->get_rect().UR.y));
		}
		}
	}

	for ( int n = 0; n < (signed)particle.size(); n++ )
	{
		if ( particle[n]->b_domagable == true )
		{
			if ( check_collision_rotated(rect, particle[n]->get_rect()) == true )
			{
				box.w--;
				box.h--;
				if ( box.w < 15 || box.h < 15 ) { b_die = true; }
				size--;

				SCORE[9]++;

					for ( int g = 9; g >= 0; g-- ) 
				{ 
					if ( SCORE[g] == 10 ) 
					{ 
						SCORE[g-1]++; SCORE[g] = 0; 
					}  
				}

				particle[n]->b_die = true; 

				rect.set(box,i_angle);

				//particle.push_back(new Particle(bulets[n]->get_rect().UR.x, bulets[n]->get_rect().UR.y));
			}
		}
	}

	if ( rand() % (size + 80)== 0 )
	{
		bulets.push_back(new Bulet(i_angle, box.x, box.y, 0.8, 0,0,0,true));
	}

}

void Enemy::move( Player &player )
{
	i_angle = calc_angle( box ,player.get_box() );

	i_xVel = calc_speed(i_angle, i_speed, 1);
	i_yVel = calc_speed(i_angle, i_speed, 0);

	box.x += i_xVel;
	box.y += i_yVel;

	rect.set(box,i_angle);

}

void Enemy::show()
{
	glPushMatrix();
		
		gluOrtho2D(0,800,600,0);

		glColor4f(150,0,0,255);

		glLineWidth(3);

		glBegin(GL_LINE_LOOP);
			glVertex2f(rect.UL.x, rect.UL.y);
			glVertex2f(rect.UR.x, rect.UR.y);
			glVertex2f(rect.LR.x, rect.LR.y);
			glVertex2f(rect.LL.x, rect.LL.y);
		glEnd();

	glPopMatrix();
}
