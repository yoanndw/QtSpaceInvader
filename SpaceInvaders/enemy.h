#pragma once

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "sprite.h"

class Enemy : public Sprite
{
	double m_spd;

public:
	Enemy(QGraphicsScene* parent, double x, double y, double spd);

	void gameUpdate() override;
};

#endif