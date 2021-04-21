#include "Collisions.h"
#include "Character.h"

//initilize to nullptr

Collisions* Collisions::m_instances = nullptr;

Collisions::Collisions()
{

}

Collisions* Collisions::Instances()
{
	if (!m_instances)
	{
		m_instances = new Collisions;
	}

	return m_instances;
}

bool Collisions::Circle(Vector2D character1, Vector2D character2, float col1, float col2)
{
	Vector2D vec = Vector2D((character1.x - character2.x), (character1.y - character2.y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combinedDistance = (col1 + col2);

	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width / 2) > rect2.x && rect1.x + (rect1.width / 2) < rect2.x + rect2.width && rect1.y + (rect1.height / 2) > rect2.y && rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Collisions::~Collisions()
{
	m_instances = nullptr;

}