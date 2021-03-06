#include "Classes.h"
#include <iostream>
#include <cmath>

void Rect::set(Box box, float angle)
{
	float x,y;
	x = box.x;
	y = box.y;

	box.x -= box.x + box.w/2;
	box.y -= box.y + box.h/2;

	UL.x = box.x * cos(-angle * 3.14159265/180) + box.y * sin(-angle * 3.14159265/180);
	UL.y = -(box.x) * sin(-angle * 3.14/180) + box.y * cos(-angle * 3.14159265/180);

	UR.x = (box.x + box.w) * cos(-angle * 3.14159265/180) + box.y * sin(-angle * 3.14159265/180);
	UR.y = -(box.x + box.w) * sin(-angle * 3.14159265/180) + box.y * cos(-angle * 3.14159265/180);

	LL.x = box.x * cos(-angle * 3.14159265/180) + (box.y + box.h)  * sin(-angle * 3.14159265/180);
	LL.y = -(box.x) * sin(-angle * 3.14159265/180) + (box.y + box.h) * cos(-angle * 3.14159265/180);

	LR.x = (box.x + box.w) * cos(-angle * 3.14159265/180) + (box.y + box.h) * sin(-angle * 3.14159265/180);
	LR.y = -(box.x + box.w) * sin(-angle * 3.14159265/180) + (box.y + box.h) * cos(-angle * 3.14159265/180);

	UL.x += x + box.w/2;
	UL.y += y + box.h/2;

	UR.x += x + box.w/2;
	UR.y += y + box.h/2;

	LL.x += x + box.w/2;
	LL.y += y + box.h/2;

	LR.x += x + box.w/2;
	LR.y += y + box.h/2;

	box.x = UL.x;
	box.y = UL.y;

}