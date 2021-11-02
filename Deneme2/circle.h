#pragma once
#include "baseShape.h"
#include <math.h>

class circle : public baseShape
{
private:
	double rad;
public:
	circle(double rad);
	double GetRadius() const;
	double GetAreaInertia() const;
	EnShapeType GetShapeType() const;
};

