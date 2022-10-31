#pragma once
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "sprite.h"

class Missile : public Sprite
{
	static const int SPD = 7;

public:
	Missile(QGraphicsScene* parent, double x, double y);

	void gameUpdate() override;
};

#endif