#pragma once
class engineListener{
public:
	virtual void runningStateChanged(bool runningState)=0;
	virtual void iterationCompleted()=0;
};


