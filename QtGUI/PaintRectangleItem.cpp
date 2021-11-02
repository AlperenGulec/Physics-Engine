#include "PaintRectangleItem.h"

PaintRectangleItem::PaintRectangleItem() : PhyItem()
{
}

void PaintRectangleItem::PaintObject(QPainter& painter)
{
	QRectF rectangle(-(this->width * 100 / 2), -(this->height * 100 / 2), this->width * 100, this->height * 100);
	painter.drawRect(rectangle);
}

