#pragma once
#include <cmath>

class point
{
private:
	double X;
	double Y;
public:
	point();
	point(double x, double y);
	double GetX();
	double GetY();
	void RotateAt(point& rotateLocation, double angle);
};

