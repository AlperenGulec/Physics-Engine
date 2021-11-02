#include "rectangle.h"

rectangle::rectangle(double width, double height)
{
    this->width = width;
    this->height = height;
}

double rectangle::GetWidth() const
{
    return this->width;
}

double rectangle::GetHeight() const
{
    return this->height;
}

double rectangle::GetAreaInertia() const
{
    return (this->width * this->width + this->height * this->height) / 12;
}

baseShape::EnShapeType rectangle::GetShapeType() const
{
    return baseShape::EnShapeType::Rectangle;
}
