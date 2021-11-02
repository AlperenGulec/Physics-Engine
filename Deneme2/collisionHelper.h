#pragma once
#include "PhyObject.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "baseShape.h"
#include "point.h"
#include "line.h"

class collisionHelper
{
private:
	static std::vector<point*> CircleToCircleCollideDetect(PhyObject* object1, PhyObject* object2);
	static std::vector<point*> CircleToRectangleCollideDetect(PhyObject* object1, PhyObject* object2);
	static std::vector<point*> RectangleToRectangleCollideDetect(PhyObject* object1, PhyObject* object2);
	static std::vector<point*> LineToCircleCollideDetect(PhyObject* circleObject, line &line);
public:
	static std::vector<point*> CollideDetect(PhyObject* object1, PhyObject* object2);
};

