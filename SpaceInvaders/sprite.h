#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPixmap>
#include <QString>

class Sprite : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

private:
	QPixmap m_pixmap;

protected:
	double m_x, m_y;
	double m_w, m_h;

public:
	Sprite(QGraphicsScene* parent, const char* image, double x, double y);

	double x() { return m_x; }
	double y() { return m_y; }

	void updatePos();
	void move(double dx, double dy);
	bool inBounds() const;

	virtual void gameUpdate() = 0;
};

#endif