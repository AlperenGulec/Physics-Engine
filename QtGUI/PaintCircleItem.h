#pragma once
#include "PhyItem.h"

class PaintCircleItem : public PhyItem
{
public:
	PaintCircleItem();
	double rad;
private:
	void PaintObject(QPainter& painter) override;
};

