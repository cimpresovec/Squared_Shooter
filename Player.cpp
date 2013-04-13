#include "Classes.h"
#include "Globals.h"
#include <SDL_opengl.h>
#include <iostream>
#include "Functions.h"

Player::Player()
{
	i_x = 400; i_y = 300;
	box.x = i_x;
	box.y = i_y;
	box.w = 25;
	box.h = 25;

	i_xVel = 0;
	i_yVel = 0;

	b_left = false;
	b_right = false;
	b_down = false;
	b_up = false;
	b_attract = false;
	b_explode = false;
	b_fakedir =  false;

	i_lives = 5;
	i_deadtime = 0;

	i_angle = 0;
	direction = NONE;
	i_level = 1;
	i_fake = 0;
	upgrade = 2;

	rect.set(box, i_angle);

	mouse.x = 0;
	mouse.y = 0;
	mouse.w = 1;
	mouse.h = 1;

};

void Player::handle_input()
{
	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_UP: b_up = true; break;
		case SDLK_RIGHT: b_right = true; break;
		case SDLK_DOWN: b_down = true; break;
		case SDLK_LEFT: b_left = true; break;
		//case SDLK_x: b_shoot = true; break;
		}

		
	}

	if ( event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN && b_attract == false )
	{
		b_shoot = true;
	}

	if ( event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONDOWN )
	{
		b_attract = true; b_shoot = false;
	}

	else if ( event.type == SDL_KEYUP )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_UP: b_up = false; break;
		case SDLK_RIGHT: b_right = false; break;
		case SDLK_DOWN: b_down = false; break;
		case SDLK_LEFT: b_left = false; break;
		//case SDLK_x: b_shoot = false; break;
		}

	}

	if ( event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP )
	{
		b_shoot = false;
	}

	
	if ( event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONUP )
	{
		b_attract = false; b_explode = true;
	}
	
	int x,y;
	SDL_GetMouseState(&x, &y);
	mouse.x = x;
	mouse.y = y;
}

Box Player::get_mouse()
{
	return mouse;
}

void Player::logic_input()
{
	if ( b_up == true && b_down == false && b_left == false && b_right == false )
	{
		direction = UP;
	}

	else if (  b_up == true && b_down == false && b_left == false && b_right == true )
	{
		direction = UPRIGHT;
	}

	else if (  b_up == false && b_down == false && b_left == false && b_right == true )
	{
		direction = RIGHT;
	}

	else if ( b_up == false && b_down == true && b_left == false && b_right == true )
	{
		direction = DOWNRIGHT;
	}

	else if ( b_up == false && b_down == true && b_left == false && b_right == false )
	{
		direction = DOWN;
	}

	else if (b_up == false && b_down == true && b_left == true && b_right == false )
	{
		direction = DOWNLEFT;
	}

	else if ( b_up == false && b_down == false && b_left == true && b_right == false )
	{
		direction = LEFT;
	}

	else if ( b_up == true && b_down == false && b_left == true && b_right == false )
	{
		direction = UPLEFT;
	}

	else if ( b_up == false && b_down == false && b_left == false && b_right == false )
	{
		direction = NONE;
	}
}

void Player::shot(std::vector<class Bulet*> &bulets, std::vector<class Particle*> &particles)
{

	if ( SCORE[7] > 0 && upgrade == 2 ) { i_level = 2; upgrade--; i_lives++; }
	if ( SCORE[7] > 4 && upgrade == 1 ) { i_level = 3; upgrade--; i_lives++; }

	if ( b_shoot == true )
	{
		if ( i_level == 1 ){
			bulets.push_back(new Bulet(i_angle, box.x, box.y, 5));}
		if ( i_level == 2 ) { 
			if ( b_fakedir == false )
			{
				i_fake+=7;
				if ( i_fake > 45 ) { b_fakedir = true;
				}
			}
			else
			{
				i_fake-=7;
				if ( i_fake < -45 ) { b_fakedir = false; }
			}
			float x = calc_speed((i_angle),5,1);
			float y = calc_speed((i_angle),5,0);

			//bulets.push_back(new Bulet((i_angle+=i_fake), box.x, box.y, 5, 1, x, y));
			bulets.push_back(new Bulet((i_angle+=i_fake), box.x, box.y, 5, 1, x, y));}

		if ( i_level == 3 ) { 
			if ( b_fakedir == false )
			{
				i_fake+=7;
				if ( i_fake > 45 ) { b_fakedir = true;
				}
			}
			else
			{
				i_fake-=7;
				if ( i_fake < -45 ) { b_fakedir = false; }
			}
			float x = calc_speed((i_angle),5,1);
			float y = calc_speed((i_angle),5,0);

			float i_blake = 0;	
			i_blake -= i_fake;
			bulets.push_back(new Bulet((i_angle+=i_blake), box.x, box.y, 5, 1, x, y));
			bulets.push_back(new Bulet((i_angle+=i_fake), box.x, box.y, 5, 1, x, y));}

	
	}


	if ( b_attract == true )
	{
		int i_count = 0;
		for ( int n = 0; n < (signed)particles.size(); n++ )
		{
			if ( particles[n]->b_domagable == false ){
				particles[n]->b_attracted = true;}
			if ( check_collision_rotated(rect,particles[n]->get_rect()) == true )
			{
				i_count++;
			}
		}
	
	}

	if ( b_attract == false && b_explode == true )
	{
		for ( int n = 0; n < (signed)particles.size(); n++ )
		{
			if ( check_collision_rotated(rect, particles[n]->get_rect()) == true )
			{
				particles[n]->b_explode = true;
			}

			particles[n]->b_attracted = false;
		}

		b_explode = false;
	}
}

Box Player::get_box()
{
	return box;
	}


void Player::check_collision(std::vector<class Bulet*> &bulets, std::vector<class Enemy*> &enemies)
{
	for ( int n = 0; n < (signed)bulets.size(); n++ )
	{
		if ( bulets[n]->b_enemy == true )
		{
			if ( i_deadtime == 0 ) {
			if ( check_collision_rotated(rect, bulets[n]->get_rect()) == true )
			{
				i_lives--;
				i_deadtime = 180;

				if ( i_lives < 0 )
				{
					set_state(MENU);
				}
			}
			}
		}
	}
	
	for ( int n = 0; n < (signed)enemies.size(); n++ )
	{
		if ( i_deadtime == 0 ) {
		if ( check_collision_rotated(rect, enemies[n]->get_rect()) == true ){
			i_lives--;
				i_deadtime = 180;
				if ( i_lives < 0 )
				{
					set_state(MENU);
				}

		}
		}
	}
}

Rect Player::get_rect()
{
	return rect;}

void Player::move()
{
	/*for ( int n = 0; n < 5; n++ ){

	switch ( direction )
	{
	case UP:
		{						
			if ( i_angle != 360 || i_angle != 0 )
			{
				if ( (0 <= i_angle && i_angle < 180) ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}

			break;
		}

	case UPRIGHT:
		{
			if ( i_angle != 45 )
			{
				if ( 45 < i_angle && i_angle < 225 ) {if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case RIGHT:
		{				
			if ( i_angle != 90 )
			{
				if ( 90 < i_angle && i_angle < 270 ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; }}
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case DOWNRIGHT:
		{						
			if ( i_angle != 135 )
			{
				if ( 135 < i_angle && i_angle < 315 ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case DOWN:
		{						
			if ( i_angle != 180 )
			{
				if ( 180 < i_angle && i_angle < 360 ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case DOWNLEFT:
		{						
			if ( i_angle != 225 )
			{
				if ( (225 < i_angle && i_angle <= 360) || (0 <= i_angle && i_angle < 45) ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case LEFT:
		{						
			if ( i_angle != 270 )
			{
				if ( (270 < i_angle && i_angle <= 360) || (0 <= i_angle && i_angle < 90) ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case UPLEFT:
		{						
			if ( i_angle != 315 )
			{
				if ( (315 < i_angle && i_angle <= 360) || (0 <= i_angle && i_angle < 135) ) 
				{ if ( i_angle-- == 0 ) { i_angle = 360; } }
				else { if ( i_angle++ == 360 ) { i_angle = 0; } }
			}


			break;
		}

	case NONE:
		{
			if ( i_yVel < 0 ) { i_yVel++; }
			else if ( i_yVel > 0 ) { i_yVel--; }

			if ( i_xVel < 0 ) { i_xVel++; }
			else if ( i_xVel > 0 ) { i_xVel--; }

			break;
		}

	}

	}*/

	i_angle = calc_angle(box,mouse);

	for ( int n = 0; n < 20; n++ ){

		switch ( direction )
	{
	case UP:
		{						

			i_yVel--;
			if ( i_xVel < 0 ) { i_xVel++; }
			else if ( i_xVel > 0 ) { i_xVel--; }

			break;
		}

	case UPRIGHT:
		{

			i_yVel--;
			i_xVel++;

			break;
		}

	case RIGHT:
		{				

			i_xVel++;
			if ( i_yVel < 0 ) { i_yVel++; }
			else if ( i_yVel > 0 ) { i_yVel--; }

			break;
		}

	case DOWNRIGHT:
		{						

			i_yVel++;
			i_xVel++;

			break;
		}

	case DOWN:
		{						

			i_yVel++;
			if ( i_xVel < 0 ) { i_xVel++; }
			else if ( i_xVel > 0 ) { i_xVel--; }

			break;
		}

	case DOWNLEFT:
		{						

			i_yVel++;
			i_xVel--;

			break;
		}

	case LEFT:
		{						

			i_xVel--;
			if ( i_yVel < 0 ) { i_yVel++; }
			else if ( i_yVel > 0 ) { i_yVel--; }


			break;
		}

	case UPLEFT:
		{						

			i_yVel--;
			i_xVel--;

			break;
		}

	case NONE:
		{
			if ( i_yVel < 0 ) { i_yVel++; }
			else if ( i_yVel > 0 ) { i_yVel--; }

			if ( i_xVel < 0 ) { i_xVel++; }
			else if ( i_xVel > 0 ) { i_xVel--; }

			break;
		}

	}

	}

	i_x += i_xVel / 50;
	i_y += i_yVel / 50;

	box.x = i_x;
	box.y = i_y;

	//if ( i_angle >= 360 ) { i_angle = 0; }
	//if ( i_angle == 0 ) { i_angle = 360; }

	if ( box.x < 0 )
	{
		box.x = 0; i_x = 0;
		i_xVel = -i_xVel;
	}

	if ( box.y < 0 )
	{
		box.y = 0; i_y = 0;
		i_yVel = -i_yVel;
	}

	if ( box.x + box.w > 800 )
	{
		box.x = 800 - box.w; i_x = box.x;
		i_xVel = -i_xVel;
	}

	if ( box.y + box.h > 600 )
	{
		box.y = 600 - box.h; i_y = box.y;
		i_yVel = -i_yVel;
	}

	if ( i_xVel > 300 )
	{
		i_xVel = 300;
	}
	else if ( i_xVel < -300 )
	{
		i_xVel = -300;
	}

	if ( i_yVel < -300 )
	{
		i_yVel = -300;
	}
	else if ( i_yVel > 300 )
	{
		i_yVel = 300;
	}

	rect.set(box,i_angle);


}

void Player::render()
{

	glPushMatrix();

		gluOrtho2D(0,800,600,0);

		glColor4d(0,1,0,1);
		/*if ( i_deadtime > 0 && (i_deadtime / 2) * 2 == i_deadtime )
		{
			glColor4d(0,1,0,0);
		}*/

		if ( i_deadtime-- < 0 ) { i_deadtime = 0; }

		glLineWidth(3);

		glBegin(GL_LINE_LOOP);
			glVertex2f(rect.UL.x, rect.UL.y);
			glVertex2f(rect.UR.x, rect.UR.y);
			glVertex2f(rect.LR.x, rect.LR.y);
			glVertex2f(rect.LL.x, rect.LL.y);		
		glEnd();

		for ( int n = 0; n < i_lives; n++ )
		{
			glBegin(GL_LINES);
				glVertex2f(10 + (n*10), 550);
				glVertex2f(10 + (n*10), 580);
			glEnd();
		}

		glColor4d(0,1,0,1);

		glTranslatef(box.x + (box.w / 2), box.y + (box.h / 2), 0 );
		glRotated(i_angle,0,0,1);
		glTranslatef(-(box.x + (box.w / 2)), -(box.y + (box.h / 2)), 0); 

		glBegin(GL_LINES);
			glVertex2f(box.x + (box.w/2), box.y + (box.h/2));
			glVertex2f((float)(box.x + (box.w/2)), (float)box.y);	
		glEnd();
		if ( i_level == 2 || i_level == 3 )
		{
			glLineWidth(1);
			if ( i_level == 3 )
			{
				glLineWidth(3);
			}
			glBegin(GL_LINE_LOOP);
				glVertex2f(box.x + 5, box.y + 5 );
				glVertex2f(box.x + box.w - 5, box.y + 5 );
				glVertex2f(box.x + box.w - 5, box.y + box.h - 5 );
				glVertex2f(box.x + 5, box.y + box.h - 5 );
			glEnd();
		}

	glPopMatrix();
	glPushMatrix();

		gluOrtho2D(0,800,600,0);
		glTranslatef(mouse.x,mouse.y,0);
			glRotated(i_angle,0,0,1);
		glTranslatef(-mouse.x,-mouse.y,0);

		glColor4d(1,1,1,1);
		glLineWidth(3);

		glBegin(GL_LINES);
			glVertex2f(mouse.x - 5, mouse.y);
			glVertex2f(mouse.x + 5, mouse.y);
			glVertex2f( mouse.x, mouse.y - 5);
			glVertex2f(mouse.x , mouse.y + 5);
		glEnd();


	glPopMatrix();

	glPushMatrix();
	
		gluOrtho2D(0,800,600,0);
		glColor4d(0,1,0,1);

		glEnable(GL_TEXTURE_2D);
		
		for ( int g = 0, x = 640; g < 10; g++, x+= 15 )
		{
			int n = SCORE[g];		

			glBindTexture(GL_TEXTURE_2D, t_numbers[n]);

			glBegin(GL_QUADS);
				/*glTexCoord2f(numbers[n].x, numbers[n].y); glVertex2f(x,550);
				glTexCoord2f(numbers[n].x+numbers[n].w,numbers[n].y); glVertex2f(x+13,550);
				glTexCoord2f(numbers[n].x+numbers[n].w, numbers[n].y +numbers[n].h); glVertex2f(x+13, 590);
				glTexCoord2f(numbers[n].x,numbers[n].y+numbers[n].h); glVertex2f(x,590);*/

				glTexCoord2f(0,0); glVertex2f(x,550);
				glTexCoord2f(1,0); glVertex2f(x+13,550);
				glTexCoord2f(1,1); glVertex2f(x+13, 590);
				glTexCoord2f(0,1); glVertex2f(x,590);
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
		
}

