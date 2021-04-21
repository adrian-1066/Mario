#pragma once
#ifndef _Collisions_H
#define _Collisions_H


#include "commons.h"

class Character;


class Collisions
{

private:
	Collisions();
	static Collisions* m_instances;
public:
	~Collisions();

	static Collisions* Instances();
	bool Circle(Vector2D character1, Vector2D character2, float col1, float col2);
	//bool Circle(Character* character1, Character* character2);
	bool Box(Rect2D rect1, Rect2D rect2);


};

#endif // !_Collisions_H