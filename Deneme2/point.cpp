#include "point.h"

point::point()
{
    this->X = 0;
    this->Y = 0;
}

point::point(double x = 0, double y = 0)
{
    this->X = x;
    this->Y = y;
}

double point::GetX()
{
    return this->X;
}

double point::GetY()
{
    return this->Y;
}

void point::RotateAt(point& rotateLocation, double angle)
{
    double shiftingOriginX = this->X - rotateLocation.X;
    double shiftingOriginY = this->Y - rotateLocation.Y;
    double shiftingRotatingX = shiftingOriginX * cos(angle) - shiftingOriginY * sin(angle);
    double shiftingRotatingY = shiftingOriginX * sin(angle) + shiftingOriginY * cos(angle);
    this->X = shiftingRotatingX + rotateLocation.X;
    this->Y = shiftingRotatingY + rotateLocation.Y;
}
