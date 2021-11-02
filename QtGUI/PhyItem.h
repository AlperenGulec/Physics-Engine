#pragma once

#include <QPainter>


class PhyItem
{
public:
	double locationX;
	double locationY;
	double Angle;
	double AngularVelocity;
	void PaintItem(QPainter& painter);
private:
	virtual void PaintObject(QPainter& painter) = 0;
};

