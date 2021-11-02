#include "PhyObject.h"
#define _USE_MATH_DEFINES
#include <cmath>

const baseShape* PhyObject::GetShape() const
{
	return this->shape;
}

PhyObject::PhyObject()
{
	this->positionX = 0;
	this->positionY = 0;
	this->velocityX = 0;
	this->velocityY = 0;
	this->mass = 1;
	this->Angle = 0;
	this->AngularVelocity = 0;
	this->shape = nullptr;
	this->state = PhyObject::ObjectState::NotFixed;
}

PhyObject::PhyObject(double posX = 0, double posY = 0, double velX = 0, double velY = 0, double mas = 1, double angle = 0, double angularVel = 0, baseShape* shape = nullptr, ObjectState state = PhyObject::ObjectState::NotFixed)
{
	this->positionX = posX;
	this->positionY = posY;
	this->velocityX = velX;
	this->velocityY = velY;
	this->mass = mas;
	this->Angle = angle;
	this->AngularVelocity = angularVel;
	this->shape = shape;
	this->state = state;
}

double PhyObject::GetPositionX() const
{
	return this->positionX;
}

double PhyObject::GetPositionY() const
{
	return (*((PhyObject*)(this))).positionY;
}

double PhyObject::GetVelocityX() const
{
	return this->velocityX;
}

double PhyObject::GetVelocityY() const
{
	return this->velocityY;
}

baseShape::EnShapeType PhyObject::GetShapeType()
{
	return this->shape->GetShapeType();
}

//double PhyObject::GetRadius() const
//{
//	return this->rad;
//}

double PhyObject::GetMass() const
{
	return this->mass;
}

double PhyObject::GetAngle() const
{
	return this->Angle;
}

double PhyObject::GetAngularVelocity() const
{
	return this->AngularVelocity;
}

double PhyObject::GetMassInertia() const
{
	return (this->GetShape()->GetAreaInertia()) * (this->mass);
}

double PhyObject::GetKineticEnergy() const
{
	return (1.0 / 2.0) * (
		(this->mass * (this->velocityX*this->velocityX + this->velocityY*velocityY))+ 
		(this->GetMassInertia() * this->AngularVelocity*this->AngularVelocity)
		);
}

void PhyObject::Tick(double timeInterval)
{
	this->positionX = this->positionX + this->velocityX * timeInterval;
	this->positionY = this->positionY + this->velocityY * timeInterval;
	this->Angle = this->Angle + (this->AngularVelocity * timeInterval);
}

void PhyObject::RollBack(double timeInterval)
{
	this->positionX = this->positionX - this->velocityX * timeInterval;
	this->positionY = this->positionY - this->velocityY * timeInterval;
	this->Angle = this->Angle - (this->AngularVelocity * timeInterval);
}


void PhyObject::changeStates(double velX, double velY, double angVel)
{
	if (this->state == PhyObject::ObjectState::NotFixed)
	{
		this->velocityX = velX;
		this->velocityY = velY;
		this->AngularVelocity = angVel;
	}
	else
	{
		this->velocityX = 0;
		this->velocityY = 0;
		this->AngularVelocity = 0;
	}

}

