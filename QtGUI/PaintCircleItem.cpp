#include "PaintCircleItem.h"

PaintCircleItem::PaintCircleItem() : PhyItem()
{
}

void PaintCircleItem::PaintObject(QPainter& painter)
{
	QRectF rectangle(-(this->rad * 100), -(this->rad * 100), (this->rad * 100) * 2, (this->rad * 100) * 2);
	painter.drawEllipse(rectangle);
}

