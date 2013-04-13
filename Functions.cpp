#include "Functions.h"
#include "Classes.h"
#include "Globals.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>
#include <SDL_image.h>
#include <cmath>
#include <iostream>

bool init()
{
	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WM_SetCaption("Shooter", NULL);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);

	SDL_SetVideoMode(800,600,32,SDL_OPENGL );

	glShadeModel(GL_SMOOTH);

	glClearColor(0,0,0,1);

	glViewport(0,0,800,600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2000 );

	return true;

}

float calc_angle( Box A, Box B )
{
	float Ax,Ay,Bx,By;

	Ax = A.x + A.w/2;
	Ay = A.y + A.h/2;
	Bx = B.x + B.w/2;
	By = B.y + B.h/2;

	double sideA, sideB, angle;

	sideA = Bx - Ax; sideB = By - Ay;

	if ( sideA < 0 ) { sideA = -sideA; } if ( sideB < 0 ) { sideB = -sideB; }

	angle = atan2(sideB,sideA) *180/3.141592654  ;

	if ( By > Ay && Bx > Ax ) { angle += 90; }
	else if ( By > Ay && Bx < Ax ) { angle += 180; }
	else if ( By < Ay && Bx < Ax ) { angle += 270; }
	else if ( Bx == Ax && By < Ay ) { angle = 0; }
	else if ( Bx == Ax && By > Ay ) { angle = 180; }
	else if ( By == Ay && Bx > Ax ) { angle = 90; }
	else if ( By == Ay && Bx < Ax ) { angle = 270; }

	float G;

	if ( angle < 90 && angle > 0 )
	{
		angle = 90 - angle;
	}

	if ( angle > 180 && angle < 270 )
	{
		angle = 270 - angle + 180;
	}



	//////////////////////LLLLLLLLLLOOOOOOOOOOOOOOOLLLLLLLLLLLLLL/////////////////

/*	if ( angle >= 90 )
	{
		angle -= 90;
	}
	else 
	{
		angle = (360 + ( angle - 90 ) );
	}*/
	G = angle;

	return (float)G;
}

float calc_speed(float angle, float xSpeed, int mode )
{
	float A;
	if ( angle >= 90 )
	{
		angle -= 90;
	}
	else 
	{
		angle = (360 + ( angle - 90 ) );
	}
	A = angle;

	if ( mode == 0 )
	{
		return (sin((A * (3.14159265/180))) * xSpeed);
	}

	else
	{
		return (cos((A * (3.14159265/180))) * xSpeed);
	}
}

bool check_collision_rotated(Rect A, Rect B)
{
	struct Axis
	{
		float x, y;
	};

	Axis axis[4] = { NULL,NULL,NULL,NULL };

	for ( int n = 0; n < 4; n++ )
	{
		switch(n)
		{
		case 0:
			{
				axis[n].x = A.UR.x - A.UL.x;
				axis[n].y = A.UR.y - A.UL.y;
				break;
			}

		case 1:
			{
				axis[n].x = A.UR.x - A.LR.x;
				axis[n].y = A.UR.y - A.LR.y;

				break;
			}

		case 2:
			{
	
				axis[n].x = B.UL.x - B.LL.x;
				axis[n].y = B.UL.y - B.LL.y;

				break;
			}

		case 3:
			{
				
				axis[n].x = B.UL.x - B.UR.x;
				axis[n].y = B.UL.y - B.UR.y;

				break;
			}
		}
	}

	bool collision = 0;

	Rect a = { NULL, NULL, NULL, NULL };
	Rect b = { NULL, NULL, NULL, NULL };

	a.UL.x = A.UL.x;
	a.UL.y = A.UL.y;
	a.UR.x = A.UR.x;
	a.UR.y = A.UR.y;
	a.LL.x = A.LL.x;
	a.LL.y = A.LL.y;
	a.LR.x = A.LR.x;
	a.LR.y = A.LR.y;

	b.UL.x = B.UL.x;
	b.UL.y = B.UL.y;
	b.UR.x = B.UR.x;
	b.UR.y = B.UR.y;
	b.LL.x = B.LL.x;
	b.LL.y = B.LL.y;
	b.LR.x = B.LR.x;
	b.LR.y = B.LR.y;

	for ( int n = 0; n < 4; n++ )
	{
		A.UR.x = ( (A.UR.x * axis[n].x + A.UR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		A.UR.y = ( (A.UR.x * axis[n].x + A.UR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;	

		A.UL.x = ( (A.UL.x * axis[n].x + A.UL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		A.UL.y = ( (A.UL.x * axis[n].x + A.UL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;	

		A.LL.x = ( (A.LL.x * axis[n].x + A.LL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		A.LL.y = ( (A.LL.x * axis[n].x + A.LL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;	

		A.LR.x = ( (A.LR.x * axis[n].x + A.LR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		A.LR.y = ( (A.LR.x * axis[n].x + A.LR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;

		B.UR.x = ( (B.UR.x * axis[n].x + B.UR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		B.UR.y = ( (B.UR.x * axis[n].x + B.UR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;	

		B.UL.x = ( (B.UL.x * axis[n].x + B.UL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		B.UL.y = ( (B.UL.x * axis[n].x + B.UL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;	

		B.LL.x = ( (B.LL.x * axis[n].x + B.LL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		B.LL.y = ( (B.LL.x * axis[n].x + B.LL.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;	

		B.LR.x = ( (B.LR.x * axis[n].x + B.LR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].x;	
		B.LR.y = ( (B.LR.x * axis[n].x + B.LR.y * axis[n].y) / ( (axis[n].x * axis[n].x) + (axis[n].y * axis[n].y) ) ) * axis[n].y;

		float minA = 9999999,minB = 9999999,maxA = -9999999, maxB = -9999999;
		float AUL,AUR,ALL,ALR,BUL,BUR,BLL,BLR;

		AUL = A.UL.x * axis[n].x + A.UL.y * axis[n].y;
		AUR = A.UR.x * axis[n].x + A.UR.y * axis[n].y;
		ALL = A.LL.x * axis[n].x + A.LL.y * axis[n].y;
		ALR = A.LR.x * axis[n].x + A.LR.y * axis[n].y;

		BUL = B.UL.x * axis[n].x + B.UL.y * axis[n].y;
		BUR = B.UR.x * axis[n].x + B.UR.y * axis[n].y;
		BLL = B.LL.x * axis[n].x + B.LL.y * axis[n].y;
		BLR = B.LR.x * axis[n].x + B.LR.y * axis[n].y;

		if ( AUL > maxA ) { maxA = AUL; }
		if ( AUR > maxA ) { maxA = AUR; }
		if ( ALL > maxA ) { maxA = ALL; }
		if ( ALR > maxA ) { maxA = ALR; }

		if ( AUL < minA ) { minA = AUL; }
		if ( AUR < minA ) { minA = AUR; }
		if ( ALL < minA ) { minA = ALL; }
		if ( ALR < minA ) { minA = ALR; }

		if ( BUL > maxB ) { maxB = BUL; }
		if ( BUR > maxB ) { maxB = BUR; }
		if ( BLL > maxB ) { maxB = BLL; }
		if ( BLR > maxB ) { maxB = BLR; }

		if ( BUL < minB ) { minB = BUL; }
		if ( BUR < minB ) { minB = BUR; }
		if ( BLL < minB ) { minB = BLL; }
		if ( BLR < minB ) { minB = BLR; }

		if ( (minB <= maxA) && (maxB >= minA) )
		{
			collision = true;

		}

		else
		{
			collision = false;
			break;
		}

		A.UL.x = a.UL.x;
		A.UL.y = a.UL.y;
		A.UR.x = a.UR.x;
		A.UR.y = a.UR.y;
		A.LL.x = a.LL.x;
		A.LL.y = a.LL.y;
		A.LR.x = a.LR.x;
		A.LR.y = a.LR.y;

		B.UL.x = b.UL.x;
		B.UL.y = b.UL.y;
		B.UR.x = b.UR.x;
		B.UR.y = b.UR.y;
		B.LL.x = b.LL.x;
		B.LL.y = b.LL.y;
		B.LR.x = b.LR.x;
		B.LR.y = b.LR.y;

	}

	return collision;

}
void set_state(gameState nextsState)
{
	nextState = nextsState;
}

void change_state()
{
	if ( nextState != NUL ){
	if ( nextState != EXIT )
	{
		switch ( nextState )
		{
		case GAME: delete currentState; currentState = new Game(); break;
		case MENU: delete currentState; currentState = new Menu(); break;
		}

	

		curState = nextState;
		nextState = NUL;
	}
	}
}
GLuint load_texture( std::string file )
{
	/*SDL_Surface * load = IMG_Load( file.c_str() );

	unsigned object(0);

	glGenTextures(1, &object);

	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, load->w, load->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, load->pixels);

	SDL_FreeSurface(load);

	return object;*/

	SDL_Surface *Image = IMG_Load(file.c_str());

    if(!Image)
        return 0;

	SDL_DisplayFormatAlpha(Image);

    unsigned Object(0);

    glGenTextures(1, &Object);

    glBindTexture(GL_TEXTURE_2D, Object);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Image->w, Image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
	Image->pixels);

    SDL_FreeSurface(Image);

    return Object;
}