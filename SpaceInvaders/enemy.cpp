#include "enemy.h"

Enemy::Enemy(QGraphicsScene* parent, double x, double y, double spd)
	: Sprite(parent, "images/enemy.png", x, y)
	, m_spd(spd)
{
}

void Enemy::gameUpdate()
{
	move(0, m_spd);
}
