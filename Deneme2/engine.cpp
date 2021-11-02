#include "engine.h"
#include <iostream>
#include "PhyObject.h"
#include <chrono>

bool engine::GetRunState()
{
    return isRunning;
}

const std::vector<const PhyObject*> engine::GetPhyObjects()
{
    return std::vector<const PhyObject*>(listOfObject.begin(), listOfObject.end());
}

engine::engine()
{
    this->listener = nullptr;
    this->isRunning = false;
}

engine::engine(engineListener* listener)
{
    this->isRunning = false;
    this->listener = listener;
}

engine::~engine()
{
    for (int i = 0; i < listOfObject.size(); ++i) {
        delete this->listOfObject[i];
    }
    if (listener != nullptr)
    {
        delete listener;
    }
}



void engine::add(PhyObject* object)
{
    (this->listOfObject).push_back(object);
}

void engine::remove()
{
    int j;
    std::cout << "place of the object: ";
    std::cin >> j;
    j = j - 1;
    (this->listOfObject).erase(std::next(listOfObject.begin() + j));
}

void engine::run()
{
    if (this->isRunning)
    {
        return;
    }
    this->isRunning = true;
    listener->runningStateChanged(this->isRunning);
    double timeInterval = 0.016;
    double gravityX = 0;
    double gravityY = 0;
    std::vector<point*> listOfIntersectionPoints = std::vector<point*>();

    while (this->isRunning) {

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (int i = 0; i < (int)(this->listOfObject).size(); ++i) {
            (this->listOfObject[i])->Tick(timeInterval);
            if (listOfObject[i]->state == PhyObject::ObjectState::NotFixed)
            {
                listOfObject[i]->velocityX += gravityX * timeInterval;
                listOfObject[i]->velocityY += gravityY * timeInterval;
            }
        }

        for (int k = 0; k < (int)(this->listOfObject).size() - 1; ++k) {
            for (int m = k + 1; m < (int)(this->listOfObject).size(); ++m)
            {
                listOfIntersectionPoints = collisionHelper::CollideDetect(listOfObject[k], listOfObject[m]);
                if (listOfIntersectionPoints.empty() == false)
                {
                    //...Ayrılıyorlar mı?..//
                    listOfObject[k]->Tick(timeInterval), listOfObject[m]->Tick(timeInterval);
                    std::vector<point*> iteratedCollisiton = collisionHelper::CollideDetect(listOfObject[k], listOfObject[m]);
                    if (iteratedCollisiton.empty())
                    {
                        for (int n = 0; n < (int)(listOfIntersectionPoints.size()); ++n)
                        {
                            delete listOfIntersectionPoints[n];
                        }
                        for (int n = 0; n < (int)(iteratedCollisiton.size()); ++n)
                        {
                            delete iteratedCollisiton[n];
                        }
                        iteratedCollisiton.clear();
                        continue;
                    }
                    for (int n = 0; n < (int)(iteratedCollisiton.size()); ++n)
                    {
                        delete iteratedCollisiton[n];
                    }
                    iteratedCollisiton.clear();
                    listOfObject[k]->RollBack(timeInterval), listOfObject[m]->RollBack(timeInterval);
                    //.................//


                    //listOfObject[k]->RollBack(timeInterval), listOfObject[m]->RollBack(timeInterval);
                    physicsHelper::newStates(listOfObject[k], listOfObject[m], listOfIntersectionPoints);
                    
                    

                    for (int n = 0; n < (int)(listOfIntersectionPoints.size()); ++n)
                    {
                        delete listOfIntersectionPoints[n];
                    }
                    
                }
            }
        }
       
        if (listener != nullptr)
        {
            listener->iterationCompleted();
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        timeInterval = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;

    }
}

void engine::stop()
{
    if (this->isRunning)
    {
        this->isRunning = false;
        this->listener->runningStateChanged(this->isRunning);
    }
}
