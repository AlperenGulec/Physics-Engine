#pragma once
#include "point.h"

class line
{
public:
	point point1;
	point point2;
	point* intersection;
	line();
	line(point point1, point point2);
	point* intersectionPoint(line& line);
	double pointToLineDistance(point& point);
};

