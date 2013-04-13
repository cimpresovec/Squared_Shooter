#include "Classes.h"
#include "Functions.h"
#include <cstdlib>
#include <iostream>

Particle::Particle(float x, float y)
{
	box.x = x;
	box.y = y;
	box.w = 1;
	box.h = 1;

	i_speed = rand() % 7;
	i_angle = rand() % 360;

	i_xVel = calc_speed(i_angle, i_speed, 1);
	i_yVel = calc_speed(i_angle, i_speed, 0);

	b_domagable = false;

	b_die = false;

	b_explode = false;
	b_attracted = false;

	rect.set(box, i_angle);
}

Rect Particle::get_rect()
{
	return rect;
}

void Particle::move( Player * player )
{

	if ( b_attracted == true && b_domagable == false )
	{
		i_xVel = calc_speed(calc_angle(box,player->get_box()), 7, 1);
		i_yVel = calc_speed(calc_angle(box,player->get_box()), 7, 0);
	}

	if ( b_explode == true )
	{
		i_xVel = calc_speed(MOUSE_ANGLE, 8, 1);
		i_yVel = calc_speed(MOUSE_ANGLE, 8, 0);

		b_explode = false;
		b_domagable = true;
		//b_attracted = false;
	}

	else if ( b_domagable == false && b_attracted == false ){
	
	if ( i_xVel > 0 )
	{
		i_xVel--;} else if ( i_xVel < 0 ) { i_xVel++; }

	if ( i_yVel > 0 )
	{
		i_yVel--;} else if ( i_yVel < 0 ) { i_yVel++; }
	}

	if ( box.x > 800 || box.x < 0 || box.y > 600 || box.y < 0 )
	{
		b_die = true;
	}

	box.x += i_xVel;
	box.y += i_yVel;

	rect.set(box,i_angle);

}

void Particle::show()
{
	glPushMatrix();
		gluOrtho2D(0,800,600,0);

		glPointSize(3);

		glColor4d(0,0,1,1);
		if ( b_domagable == true )
		{
			glColor4d(0,1,1,1);
		}

		glBegin(GL_POINTS);
			glVertex2f(box.x, box.y); 
		glEnd();
	glPopMatrix();
}