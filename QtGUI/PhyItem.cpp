#include "PhyItem.h"

void PhyItem::PaintItem(QPainter& painter)
{
	painter.translate(QPoint(this->locationX * 100, this->locationY * 100));
	painter.rotate(this->Angle*180/M_PI);
	this->PaintObject(painter);
	painter.resetTransform();

}
