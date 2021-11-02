#pragma once
#include "PhyObject.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "line.h"
#include "point.h"

class physicsHelper
{
public:
	static void newStates(PhyObject* object1, PhyObject* object2, std::vector<point*> listOfIntersectionPoints);
};

