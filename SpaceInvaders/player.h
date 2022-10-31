#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sprite.h"

#include <QTimer>

class Player : public Sprite
{
public:
	Player(QGraphicsScene* parent, double x, double y);

	void gameUpdate() override;
};

#endif