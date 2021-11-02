#pragma once


class baseShape
{

public:
	
	enum class EnShapeType
	{
		Circle,
		Rectangle,
	};
	virtual EnShapeType GetShapeType() const = 0;
	virtual double GetAreaInertia() const = 0;
};

