#include "sprite.h"

#include <QPixmap>

#include "globalconsts.h"

Sprite::Sprite(QGraphicsScene* parent, const char* image, double x, double y)
	: QObject(parent)
	, QGraphicsPixmapItem(QPixmap(image))
	, m_pixmap(image)
	, m_x(x)
	, m_y(y)
	, m_w(m_pixmap.width())
	, m_h(m_pixmap.height())
{
	updatePos();
}

void Sprite::updatePos()
{
	setPos(m_x, m_y);
}

void Sprite::move(double dx, double dy)
{
	m_x += dx;
	m_y += dy;
	updatePos();
}

bool Sprite::inBounds() const
{
	bool inBoundsX = m_x + m_w >= 0 && m_x <= WIN_W;
	bool inBoundsY = m_y + m_h >= 0 && m_y <= WIN_H;

	return inBoundsX && inBoundsY;
}
