#include "line.h"

line::line()
{
	this->intersection = nullptr;
}

line::line(point point1, point point2)
{
	this->point1 = point1;
	this->point2 = point2;
}

point* line::intersectionPoint(line& line)
{
	double A1 = this->point2.GetY() - this->point1.GetY();
	double B1 = this->point1.GetX() - this->point2.GetX();
	double C1 = A1 * (this->point1.GetX()) + B1 * (this->point1.GetY());

	double A2 = line.point2.GetY() - line.point1.GetY();
	double B2 = line.point1.GetX() - line.point2.GetX();
	double C2 = A2 * (line.point1.GetX()) + B2 * (line.point1.GetY());

	double intersectionX = 0;
	double intersectionY = 0;

	double det = A1 * B2 - A2 * B1;
	if (det == 0) {
		//Lines are parallel
		return nullptr;
	}
	else
	{
		intersectionX = (B2 * C1 - B1 * C2) / det;
		intersectionY = (A1 * C2 - A2 * C1) / det;
	}

	if (((intersectionX >= this->point1.GetX() && intersectionX <= this->point2.GetX()) || (intersectionX >= this->point2.GetX() && intersectionX <= this->point1.GetX()) || (intersectionY >= this->point1.GetY() && intersectionY <= this->point2.GetY()) || (intersectionY >= this->point2.GetY() && intersectionY <= this->point1.GetY())) && ((intersectionX >= line.point1.GetX() && intersectionX <= line.point2.GetX()) || (intersectionX >= line.point2.GetX() && intersectionX <= line.point1.GetX()) || (intersectionY >= line.point1.GetY() && intersectionY <= line.point2.GetY()) || (intersectionY >= line.point2.GetY() && intersectionY <= line.point1.GetY())))
	{
		intersection = new point(intersectionX, intersectionY);
		return intersection;	
	}
	else
	{
		return nullptr;
	}
}

double line::pointToLineDistance(point& point)
{
	return ((this->point2.GetX() - this->point1.GetX()) * (this->point1.GetY() - point.GetY()) - (this->point1.GetX() - point.GetX()) * (this->point2.GetY() - this->point1.GetY())) / (sqrt(pow(this->point2.GetX() - this->point1.GetX(), 2) + pow(this->point2.GetY() - this->point1.GetY(), 2)));
}
