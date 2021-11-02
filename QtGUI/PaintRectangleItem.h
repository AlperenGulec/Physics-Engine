#pragma once
#include "PhyItem.h"


class PaintRectangleItem : public PhyItem
{	
public:
	PaintRectangleItem();
	double width;
	double height;
private:
	void PaintObject(QPainter& painter) override;
};

