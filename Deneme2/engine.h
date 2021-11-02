#pragma once
#include <vector>
#include "PhyObject.h"
#include "engineListener.h"
#include "collisionHelper.h"
#include "physicsHelper.h"

class engine
{
private:
	std::vector<PhyObject*> listOfObject = std::vector<PhyObject*>();
	bool isRunning;
	engineListener* listener;
public:
	bool GetRunState();//is running e erişelim.
	const std::vector<const PhyObject*> GetPhyObjects();
	engine();
	engine(engineListener* listener);
	~engine();
	void add(PhyObject* object);
	void remove();
	void run();
	void stop();
};

