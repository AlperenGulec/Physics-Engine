#include "physicsHelper.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

void physicsHelper::newStates(PhyObject* object1, PhyObject* object2, std::vector<point*> listOfIntersectionPoints)
{
	double intersectionX = 0;
	double intersectionY = 0;
	for (int i = 0; i < (int)(listOfIntersectionPoints.size()); ++i)
	{
		intersectionX += listOfIntersectionPoints[i]->GetX();
		intersectionY += listOfIntersectionPoints[i]->GetY();
	}
	if (listOfIntersectionPoints[0]->GetX() == listOfIntersectionPoints[1]->GetX() && listOfIntersectionPoints[0]->GetY() == listOfIntersectionPoints[1]->GetY())
	{
		return;
	}

	point centerPointCollisionLine = point(intersectionX / (double)(listOfIntersectionPoints.size()), intersectionY / (double)(listOfIntersectionPoints.size()));
	
	point impulseLineSecondPoint = *listOfIntersectionPoints[0];
	impulseLineSecondPoint.RotateAt(centerPointCollisionLine, M_PI_2);
	
	line impulseLine = line(centerPointCollisionLine, impulseLineSecondPoint);
	point centerPointObject1 = point(object1->positionX, object1->positionY);
	point centerPointObject2 = point(object2->positionX, object2->positionY);

	double d1 = impulseLine.pointToLineDistance(centerPointObject1);
	double d2 = impulseLine.pointToLineDistance(centerPointObject2);
	if (d1<1e-15 && d1>-1e-15)
	{
		d1 = 0;
	}
	if (d2<1e-15 && d2>-1e-15)
	{
		d2 = 0;
	}

	double m1 = object1->mass;
	double m2 = object2->mass;
	double In1 = object1->GetMassInertia();
	double In2 = object2->GetMassInertia();
	double Vx1 = object1->velocityX;
	double Vy1 = object1->velocityY;
	double Vx2 = object2->velocityX;
	double Vy2 = object2->velocityY;
	double w1 = object1->AngularVelocity;
	double w2 = object2->AngularVelocity;
	double alfa = atan2(impulseLineSecondPoint.GetY() - centerPointCollisionLine.GetY(), impulseLineSecondPoint.GetX() - centerPointCollisionLine.GetX()) - M_PI;
	double E = object1->GetKineticEnergy() + object2->GetKineticEnergy();
	double I = NAN;

	double newVx1 = 0;
	double newVy1 = 0;
	double newVx2 = 0;
	double newVy2 = 0;
	double newW1 = 0;
	double newW2 = 0;



	//if (object1->state == PhyObject::ObjectState::Fixed)
	//{
	//	I = -2 * (d2 * w2 + Vx2 * cos(alfa) + Vy2 * sin(alfa)) / (pow(cos(alfa), 2) / m2 + pow(sin(alfa), 2) / m2 + pow(d2, 2) / In2);
	//	if (isnan(I))
	//	{
	//		return;
	//	}
	//	double Ix = (I * cos(alfa));
	//	double Iy = (I * sin(alfa));
	//	if (Ix<1e-7 && Ix>-1e-7)
	//	{
	//		Ix = 0;
	//	}
	//	if (Iy<1e-7 && Iy>-1e-7)
	//	{
	//		Iy = 0;
	//	}
	//	newVx1 = 0;
	//	newVy1 = 0;
	//	newVx2 = Vx2 + Ix / m2;
	//	newVy2 = Vy2 + Iy / m2;
	//	newW1 = 0;
	//	newW2 = w2 + (I * d2 / In2);
	//}

	//else if (object2->state == PhyObject::ObjectState::Fixed)
	//{
	//	I = -2 * (d1 * w1 + Vx1 * cos(alfa) + Vy1 * sin(alfa)) / (pow(cos(alfa), 2) / m1 + pow(sin(alfa), 2) / m1 + pow(d1, 2) / In1);
	//	if (isnan(I))
	//	{
	//		return;
	//	}
	//	double Ix = (I * cos(alfa));
	//	double Iy = (I * sin(alfa));
	//	if (Ix<1e-7 && Ix>-1e-7)
	//	{
	//		Ix = 0;
	//	}
	//	if (Iy<1e-7 && Iy>-1e-7)
	//	{
	//		Iy = 0;
	//	}
	//	newVx1 = Vx1 + Ix / m1;
	//	newVy1 = Vy1 + Iy / m1;
	//	newVx2 = 0;
	//	newVy2 = 0;
	//	newW1 = w1 + (I * d1 / In1);
	//	newW2 = 0;
	//}

	//else
	//{
		I = -2 * (d1 * w1 - d2 * w2 + Vx1 * cos(alfa) - Vx2 * cos(alfa) + Vy1 * sin(alfa) - Vy2 * sin(alfa)) / (pow(cos(alfa), 2) / m1 + pow(cos(alfa), 2) / m2 + pow(sin(alfa), 2) / m1 + pow(sin(alfa), 2) / m2 + pow(d1, 2) / In1 + pow(d2, 2) / In2);
		if (isnan(I))
		{
			return;
		}
		double Ix = (I * cos(alfa));
		double Iy = (I * sin(alfa));
		if (Ix<1e-5 && Ix>-1e-5)
		{
			Ix = 0;
		}
		if (Iy<1e-5 && Iy>-1e-5)
		{
			Iy = 0;
		}
		newVx1 = Vx1 + Ix/ m1;
		newVy1 = Vy1 + Iy / m1;
		newVx2 = Vx2 - Ix / m2;
		newVy2 = Vy2 - Iy / m2;
		newW1 = w1 + (I * d1 / In1);
		newW2 = w2 - (I * d2 / In2);
	//}
	
	object1->changeStates(newVx1, newVy1, newW1);
	object2->changeStates(newVx2, newVy2, newW2);
}

