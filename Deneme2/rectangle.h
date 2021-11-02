#pragma once
#include "baseShape.h"

class rectangle : public baseShape
{
private:
	double width;
	double height;
public:
	rectangle(double width, double height);
	double GetWidth() const;
	double GetHeight() const;
	double GetAreaInertia() const;
	EnShapeType GetShapeType() const;
};

