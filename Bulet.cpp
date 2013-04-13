#include "Classes.h"
#include "Globals.h"
#include "Functions.h"
#include <SDL_opengl.h>
#include <iostream>

Bulet::Bulet( float angle, int x, int y, float speed, int mode, float xVel, float yVel, bool ene)
{
	i_angle = angle;

	i_xVel = calc_speed(i_angle, 5, 1);
	i_yVel = calc_speed(i_angle, 5, 0);

	if ( mode == 1 )
	{
		box.x = (float)x + 12; box.y = (float)y + 13;
		box.x += i_xVel*3; box.y += i_yVel*3;
		box.w = 1;
		box.h = 1;

		i_xVel = xVel;
		i_yVel = yVel;
	}

	else if ( mode == 0 )
	{
		box.x = (float)x + 12; box.y = (float)y + 13;
		box.x += i_xVel*3; box.y += i_yVel*3;
		box.w = 1;
		box.h = 1;
	}

	b_enemy = false;
	if ( ene == true ) { b_enemy = true; }

	rect.set(box,0);

	b_die = false;
}

Rect Bulet::get_rect()
{
	return rect;
}

void Bulet::move()
{
	box.x += i_xVel;
	box.y += i_yVel;

	if ( box.x > 800 || box.y > 600 || box.x < 0 || box.y < 0 )
	{
		b_die = true;
	}

	rect.set(box,0);
};

void Bulet::show()
{
	glPushMatrix();

		gluOrtho2D(0,800,600,0);
		glColor4d(0,1,0,1);
		glPointSize(4);
		if ( b_enemy == true )
		{
			glColor4d(1,1,0,1);
			glPointSize(6);
		}

		

		glBegin(GL_POINTS);
			glVertex2f(box.x,box.y);
		glEnd();

	glPopMatrix();
}
