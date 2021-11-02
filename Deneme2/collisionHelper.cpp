#include "collisionHelper.h"
#include "rectangle.h"

std::vector<point*> collisionHelper::CollideDetect(PhyObject* object1, PhyObject* object2)
{

	if (object1->GetShapeType() == baseShape::EnShapeType::Circle && object2->GetShapeType() == baseShape::EnShapeType::Circle)
	{
		return CircleToCircleCollideDetect(object1, object2);
	}

	else if (object1->GetShapeType() == baseShape::EnShapeType::Circle && object2->GetShapeType() == baseShape::EnShapeType::Rectangle)
	{
		return CircleToRectangleCollideDetect(object1, object2);
	}

	else if (object1->GetShapeType() == baseShape::EnShapeType::Rectangle && object2->GetShapeType() == baseShape::EnShapeType::Circle)
	{
		return CircleToRectangleCollideDetect(object2, object1);
	}

	else if (object1->GetShapeType() == baseShape::EnShapeType::Rectangle && object2->GetShapeType() == baseShape::EnShapeType::Rectangle)
	{
		return RectangleToRectangleCollideDetect(object1, object2);
	}

	else
	{
		return std::vector<point*>();
	}
}

std::vector<point*> collisionHelper::CircleToCircleCollideDetect(PhyObject* object1, PhyObject* object2)
{
	const baseShape* shapePointer1 = object1->GetShape();
	const circle* circleShape1 = dynamic_cast<const circle*>(shapePointer1);
	const baseShape* shapePointer2 = object2->GetShape();
	const circle* circleShape2 = dynamic_cast<const circle*>(shapePointer2);
	//return sqrt((pow((object1->GetPositionX() - object2->GetPositionX()), 2) + pow((object1->GetPositionY() - object2->GetPositionY()), 2))) < (circleShape1->GetRadius() + circleShape2->GetRadius());;

	double R = sqrt(pow(object2->GetPositionX() - object1->GetPositionX(), 2) + pow(object2->GetPositionY() - object1->GetPositionY(), 2));
	double x1 = (0.5) * (object1->GetPositionX() + object2->GetPositionX()) + ((pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2)) / 2 * pow(R, 2)) * (object2->GetPositionX() - object1->GetPositionX()) + (0.5) * sqrt(2 * ((pow(circleShape1->GetRadius(), 2) + pow(circleShape2->GetRadius(), 2)) / pow(R, 2)) - (pow(pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2), 2) / pow(R, 4)) - 1) * (object2->GetPositionY() - object1->GetPositionY());
	double y1 = (0.5) * (object1->GetPositionY() + object2->GetPositionY()) + ((pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2)) / 2 * pow(R, 2)) * (object2->GetPositionY() - object1->GetPositionY()) + (0.5) * sqrt(2 * ((pow(circleShape1->GetRadius(), 2) + pow(circleShape2->GetRadius(), 2)) / pow(R, 2)) - (pow(pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2), 2) / pow(R, 4)) - 1) * (object1->GetPositionX() - object2->GetPositionX());
	double x2 = (0.5) * (object1->GetPositionX() + object2->GetPositionX()) + ((pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2)) / 2 * pow(R, 2)) * (object2->GetPositionX() - object1->GetPositionX()) - (0.5) * sqrt(2 * ((pow(circleShape1->GetRadius(), 2) + pow(circleShape2->GetRadius(), 2)) / pow(R, 2)) - (pow(pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2), 2) / pow(R, 4)) - 1) * (object2->GetPositionY() - object1->GetPositionY());
	double y2 = (0.5) * (object1->GetPositionY() + object2->GetPositionY()) + ((pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2)) / 2 * pow(R, 2)) * (object2->GetPositionY() - object1->GetPositionY()) - (0.5) * sqrt(2 * ((pow(circleShape1->GetRadius(), 2) + pow(circleShape2->GetRadius(), 2)) / pow(R, 2)) - (pow(pow(circleShape1->GetRadius(), 2) - pow(circleShape2->GetRadius(), 2), 2) / pow(R, 4)) - 1) * (object1->GetPositionX() - object2->GetPositionX());
	std::vector<point*> listOfIntersectionPoints = std::vector<point*>();

	if (sqrt((pow((object1->GetPositionX() - object2->GetPositionX()), 2) + pow((object1->GetPositionY() - object2->GetPositionY()), 2))) < (circleShape1->GetRadius() + circleShape2->GetRadius()))
	{
		listOfIntersectionPoints.push_back(new point(x1, y1));
		listOfIntersectionPoints.push_back(new point(x2, y2));

		if (listOfIntersectionPoints.size() < 2)
		{
			for (int n = 0; n < (int)(listOfIntersectionPoints.size()); ++n)
			{
				delete listOfIntersectionPoints[n];
			}
			listOfIntersectionPoints.clear();
		}
		return listOfIntersectionPoints;
	}
	else
	{
		return std::vector<point*>();
	}
	
}

std::vector<point*> collisionHelper::CircleToRectangleCollideDetect(PhyObject* object1, PhyObject* object2)
{
	const baseShape* shapePointer1 = object1->GetShape();
	const circle* circleShape1 = dynamic_cast<const circle*>(shapePointer1);
	const baseShape* shapePointer2 = object2->GetShape();
	const rectangle* rectangleShape2 = dynamic_cast<const rectangle*>(shapePointer2);

	std::vector<line> listOfLinesObject2 = std::vector<line>();
	std::vector<point*> listOfIntersectionPoints = std::vector<point*>();
	std::vector<point*> smallListOfIntersectionPoints = std::vector<point*>();

	point point1o2 = point(object2->GetPositionX() + rectangleShape2->GetWidth() / 2, object2->GetPositionY() + rectangleShape2->GetHeight() / 2);
	point point2o2 = point(object2->GetPositionX() + rectangleShape2->GetWidth() / 2, object2->GetPositionY() - rectangleShape2->GetHeight() / 2);
	point point3o2 = point(object2->GetPositionX() - rectangleShape2->GetWidth() / 2, object2->GetPositionY() + rectangleShape2->GetHeight() / 2);
	point point4o2 = point(object2->GetPositionX() - rectangleShape2->GetWidth() / 2, object2->GetPositionY() - rectangleShape2->GetHeight() / 2);
	point rectangleCenter = point(object2->GetPositionX(), object2->GetPositionY());
	
	point1o2.RotateAt(rectangleCenter, object2->GetAngle());
	point2o2.RotateAt(rectangleCenter, object2->GetAngle());
	point3o2.RotateAt(rectangleCenter, object2->GetAngle());
	point4o2.RotateAt(rectangleCenter, object2->GetAngle());

	listOfLinesObject2.push_back(line(point1o2, point2o2));
	listOfLinesObject2.push_back(line(point2o2, point4o2));
	listOfLinesObject2.push_back(line(point4o2, point3o2));
	listOfLinesObject2.push_back(line(point3o2, point1o2));


	for (int i = 0; i < (int)(listOfLinesObject2.size()); ++i)
	{
		smallListOfIntersectionPoints = LineToCircleCollideDetect(object1, listOfLinesObject2[i]);
		for (int j = 0; j < (int)(smallListOfIntersectionPoints.size()); ++j)
		{
			listOfIntersectionPoints.push_back(smallListOfIntersectionPoints[j]);
		}
		smallListOfIntersectionPoints.clear();
	}

	if (listOfIntersectionPoints.size() < 2)
	{
		for (int n = 0; n < (int)(listOfIntersectionPoints.size()); ++n)
		{
			delete listOfIntersectionPoints[n];
		}
		listOfIntersectionPoints.clear();
	}

	return listOfIntersectionPoints;
}

std::vector<point*> collisionHelper::RectangleToRectangleCollideDetect(PhyObject* object1, PhyObject* object2)
{
	const baseShape* shapePointer1 = object1->GetShape();
	const rectangle* rectangleShape1 = dynamic_cast<const rectangle*>(shapePointer1);
	const baseShape* shapePointer2 = object2->GetShape();
	const rectangle* rectangleShape2 = dynamic_cast<const rectangle*>(shapePointer2);

	std::vector<point> listOfPointsObject1 = std::vector<point>();
	std::vector<point> listOfPointsObject2 = std::vector<point>();
	std::vector<line> listOfLinesObject1 = std::vector<line>();
	std::vector<line> listOfLinesObject2 = std::vector<line>();
	std::vector<point*> listOfIntersectionPoints = std::vector<point*>();

	point object1Center = point(object1->GetPositionX(), object1->GetPositionY());
	point object2Center = point(object2->GetPositionX(), object2->GetPositionY());

	// create rectangle's points by giving points' x and y coordinates
	listOfPointsObject1.push_back(point(object1->GetPositionX() + rectangleShape1->GetWidth() / 2, object1->GetPositionY() + rectangleShape1->GetHeight() / 2));
	listOfPointsObject1.push_back(point(object1->GetPositionX() + rectangleShape1->GetWidth() / 2, object1->GetPositionY() - rectangleShape1->GetHeight() / 2));
	listOfPointsObject1.push_back(point(object1->GetPositionX() - rectangleShape1->GetWidth() / 2, object1->GetPositionY() + rectangleShape1->GetHeight() / 2));
	listOfPointsObject1.push_back(point(object1->GetPositionX() - rectangleShape1->GetWidth() / 2, object1->GetPositionY() - rectangleShape1->GetHeight() / 2));

	listOfPointsObject2.push_back(point(object2->GetPositionX() + rectangleShape2->GetWidth() / 2, object2->GetPositionY() + rectangleShape2->GetHeight() / 2));
	listOfPointsObject2.push_back(point(object2->GetPositionX() + rectangleShape2->GetWidth() / 2, object2->GetPositionY() - rectangleShape2->GetHeight() / 2));
	listOfPointsObject2.push_back(point(object2->GetPositionX() - rectangleShape2->GetWidth() / 2, object2->GetPositionY() + rectangleShape2->GetHeight() / 2));
	listOfPointsObject2.push_back(point(object2->GetPositionX() - rectangleShape2->GetWidth() / 2, object2->GetPositionY() - rectangleShape2->GetHeight() / 2));

	for (int m = 0; m < (int)(listOfPointsObject1.size()); ++m)
	{
		listOfPointsObject1[m].RotateAt(object1Center, object1->GetAngle());
		listOfPointsObject2[m].RotateAt(object2Center, object2->GetAngle());
	}

	listOfLinesObject1.push_back(line(listOfPointsObject1[0], listOfPointsObject1[1]));
	listOfLinesObject1.push_back(line(listOfPointsObject1[1], listOfPointsObject1[3]));
	listOfLinesObject1.push_back(line(listOfPointsObject1[3], listOfPointsObject1[2]));
	listOfLinesObject1.push_back(line(listOfPointsObject1[2], listOfPointsObject1[0]));

	listOfLinesObject2.push_back(line(listOfPointsObject2[0], listOfPointsObject2[1]));
	listOfLinesObject2.push_back(line(listOfPointsObject2[1], listOfPointsObject2[3]));
	listOfLinesObject2.push_back(line(listOfPointsObject2[3], listOfPointsObject2[2]));
	listOfLinesObject2.push_back(line(listOfPointsObject2[2], listOfPointsObject2[0]));

	for (int i = 0; i < (int)(listOfLinesObject1.size()); ++i)
	{
		for (int j = 0; j < (int)(listOfLinesObject2.size()); ++j)
		{
			if (listOfLinesObject1[i].intersectionPoint(listOfLinesObject2[j]) != nullptr)
			{
				listOfIntersectionPoints.push_back(listOfLinesObject1[i].intersectionPoint(listOfLinesObject2[j]));
			}
		}
	}
	if (listOfIntersectionPoints.size() < 2)
	{
		for (int n = 0; n < (int)(listOfIntersectionPoints.size()); ++n)
		{
			delete listOfIntersectionPoints[n];
		}
		listOfIntersectionPoints.clear();
	}

	return listOfIntersectionPoints;
}

std::vector<point*> collisionHelper::LineToCircleCollideDetect(PhyObject* circleObject, line& line)
{
	const baseShape* shapePointer = circleObject->GetShape();
	const circle* circleShape = dynamic_cast<const circle*>(shapePointer);

	double dx = line.point2.GetX() - line.point1.GetX();
	double dy = line.point2.GetY() - line.point1.GetY();
	double dr = sqrt(pow(dx,2) + pow(dy,2));
	double D = (line.point1.GetX() - circleObject->GetPositionX()) * (line.point2.GetY() - circleObject->GetPositionY()) - (line.point2.GetX() - circleObject->GetPositionX()) * (line.point1.GetY() - circleObject->GetPositionY());
	double discriminant = pow(circleShape->GetRadius(), 2) * pow(dr, 2) - pow(D, 2);
	if (discriminant < 1e-7 )
	{
		return std::vector<point*>();
	}
	double sgn = 0;
	if (dy < 0)
	{
		sgn = -1;
	}
	else
	{
		sgn = 1;
	}
	double intersectionX1 = ((D * dy + sgn * dx * sqrt(discriminant)) / pow(dr, 2)) + circleObject->GetPositionX();
	double intersectionY1 = ((-D * dx + abs(dy) * sqrt(discriminant)) / pow(dr, 2)) + circleObject->GetPositionY();

	double intersectionX2 = ((D * dy - sgn * dx * sqrt(discriminant)) / pow(dr, 2)) + circleObject->GetPositionX();
	double intersectionY2 = ((-D * dx - abs(dy) * sqrt(discriminant)) / pow(dr, 2)) + circleObject->GetPositionY();

	std::vector<point*> listOfIntersectionPoints = std::vector<point*>();

	if (((intersectionX1 >= line.point1.GetX() && intersectionX1 <= line.point2.GetX()) || (intersectionX1 >= line.point2.GetX() && intersectionX1 <= line.point1.GetX()) || (intersectionY1 >= line.point1.GetY() && intersectionY1 <= line.point2.GetY()) || (intersectionY1 >= line.point2.GetY() && intersectionY1 <= line.point1.GetY())))
	{
		listOfIntersectionPoints.push_back(new point(intersectionX1, intersectionY1));

	}
	if (((intersectionX2 >= line.point1.GetX() && intersectionX2 <= line.point2.GetX()) || (intersectionX2 >= line.point2.GetX() && intersectionX2 <= line.point1.GetX()) || (intersectionY2 >= line.point1.GetY() && intersectionY2 <= line.point2.GetY()) || (intersectionY2 >= line.point2.GetY() && intersectionY2 <= line.point1.GetY())))
	{
		listOfIntersectionPoints.push_back(new point(intersectionX2, intersectionY2));
	}

	return listOfIntersectionPoints;
}
