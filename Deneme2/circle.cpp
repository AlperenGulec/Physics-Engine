#include "circle.h"
#include <math.h>

circle::circle(double rad)
{
    this->rad = rad;
}

double circle::GetRadius() const
{
    return this->rad;
}

double circle::GetAreaInertia() const
{
    return pow(this->rad, 2) / 4;
}

baseShape::EnShapeType circle::GetShapeType() const
{
    return baseShape::EnShapeType::Circle;
}
