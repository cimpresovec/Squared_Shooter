#ifndef CLASSES_H
#define CLASSES_H

#include <SDL.h>
#include <vector>

enum State
{
	UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, NONE };

struct Box
{
	float x,y,w,h;
};

struct Rect
{
	Box UL, UR, LL, LR;

	void set(Box box, float angle);
};

class Bulet
{
private:

	Box box;

	float i_x, i_y;

	float i_xVel, i_yVel;

	float i_angle;

	Rect rect;

public:

	bool b_die;
	bool b_enemy;

	Bulet( float angle, int x, int y, float speed, int mode = NULL, float xVel = NULL, float yVel = NULL, bool ene = false );

	void move();
	void show();

	Rect get_rect();
};

class Player;

class Particle
{
private:

	Box box;

	float i_xVel, i_yVel;

	float i_angle;

	float i_speed;

	Rect rect;

public:

	bool b_domagable;
	bool b_attracted;
	bool b_explode;

	bool b_die;

	Particle ( float x, float y );

	void move( Player* player );
	void show();

	Rect get_rect();
};

class Player
{
private:
	float i_x, i_y;

	float i_xVel, i_yVel;

	Box mouse;

	Box box;

	Rect rect;

	bool b_left, b_right, b_up, b_down, b_shoot, b_attract, b_explode;

	State direction;

	float i_angle;

	int i_level;
	int i_lives;
	int i_deadtime;

	bool b_fakedir;
	int i_fake;

	int upgrade;

public:

	Player();

	void handle_input();
	void logic_input();
	void move();
	void render();
	void shot ( std::vector<class Bulet*>  &bulets, std::vector<class Particle*> &particles );
	void check_collision( std::vector<class Bulet*>  &bulets, std::vector<class Enemy*>  &enemies );

	Box get_box();
	Rect get_rect();
	Box get_mouse();
};

class Enemy
{
private:
	Box box;
	Rect rect;

	int size;

	float i_xVel, i_yVel;

	float i_speed;

	float i_angle;

public:

	bool b_die;

	Enemy( int level );

	void move( Player &player );

	void check_collision( std::vector<Bulet*> &bulets, std::vector<Particle*> &particle );

	void show();

	Rect get_rect();
};

class GameState
{
public:

	virtual void handle_input();
	virtual void logic();
	virtual void render();
};

class Menu : public GameState
{
public:	

	Menu();

	void handle_input();
	void logic();
	void render();
};

class Game : public GameState
{
private:
	Player o_player;

	std::vector<class Bulet*> o_bulets;
	std::vector<class Enemy*> o_enemies;
	std::vector<class Particle*> o_particles;

	float i_enemiesLevel;

public:

	Game();

	void handle_input();
	void logic();
	void render();
};

#endif
