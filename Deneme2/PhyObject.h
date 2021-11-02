#pragma once
#include "baseShape.h"
#include <vector>
#include "circle.h"
#include "rectangle.h"

class physicsHelper;
class engine;
class PhyObject
{
private:
	double positionX;
	double positionY;
	double velocityX;
	double velocityY;
	double mass;
	double Angle;
	double AngularVelocity;
	baseShape* shape;
	void changeStates(double velX, double velY, double angVel);
public:
	enum class ObjectState
	{
		Fixed,
		NotFixed,
	};
	enum PhyObject::ObjectState state;
    const baseShape* GetShape() const;
	PhyObject();
	PhyObject(double posX, double posY, double velX, double velY, double mas, double angle, double angularVel, baseShape* shape, ObjectState state);
	double GetPositionX() const;
	double GetPositionY() const;
	double GetVelocityX() const;
	double GetVelocityY() const;
	double GetMass() const;
	double GetAngle() const;
	double GetAngularVelocity() const;
	double GetKineticEnergy() const;
	double GetMassInertia() const;
	baseShape::EnShapeType GetShapeType();
	void Tick(double timeInterval);
	void RollBack(double timeInterval);
	friend class physicsHelper;
	friend class engine;
};

