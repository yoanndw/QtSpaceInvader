#include "enemy.h"
#include "missile.h"

#include <iostream>

Missile::Missile(QGraphicsScene* parent, double x, double y)
	: Sprite(parent, "images/missile.png", x, y)
{
}

void Missile::gameUpdate()
{
	move(0, -SPD);

	// Collision
	QList<QGraphicsItem*> collidings = collidingItems();

	for (int i = collidings.length() - 1; i >= 0; i--)
	{
		// L'objet touché est un Enemy
		auto* item = collidings[i];
		if (typeid(item) == typeid(Enemy*))
		{
			scene()->addEllipse(200, 220, 50, 50);
			scene()->removeItem(item);

			delete item;
			collidings.removeAt(i);
		}
	}
}

