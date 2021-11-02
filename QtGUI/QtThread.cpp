#include "QtThread.h"
#include <QDebug>
#include <QMutex>
#include "circle.h"
#include "rectangle.h"

QtThread::QtThread(QObject* parent, bool b) :
    QThread(parent), Stop(b)
{
    this->en = new engine(this);
    //PhyObject* obj = new PhyObject(0.1, 1, 400, 0, 0.01, 0, 0, (new circle(0.04)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj2 = new PhyObject(1, 3, 2, 1.5, 30, 0, 0, (new circle(0.4)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj3 = new PhyObject(14, 4, -1, 0, 10, 0, 0, (new circle(0.3)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj4 = new PhyObject(7, 1, 1, 1, 20, 0, 0, (new circle(0.3)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj5 = new PhyObject(7, 6, 2, -1, 10, 0, 0, (new circle(0.25)), PhyObject::ObjectState::NotFixed);
    //PhyObject* obj6 = new PhyObject(6.5, 4, 3, 0, 10, 0, 0, (new circle(0.3)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj7 = new PhyObject(7.5, 3.5, 0, 0, 1000000,0, 0, (new rectangle(15,7)), PhyObject::ObjectState::Fixed);
    //PhyObject* obj4 = new PhyObject(7.5, 0.4, -10, 0, 10, 0, 0, (new circle(0.3)), PhyObject::ObjectState::NotFixed);
    //PhyObject* obj5 = new PhyObject(4.3, 3.6, 0, 10, 10, 0, 0, (new circle(0.3)), PhyObject::ObjectState::NotFixed);
    //PhyObject* obj6 = new PhyObject(10.7, 3.6, 0, -10, 10, 0, 0, (new circle(0.3)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj8 = new PhyObject(14, 6, -2, -1, 15, 0, 0.5, (new rectangle(0.5, 0.5)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj9 = new PhyObject(1, 1, 1, 1.5, 10, 0, 0, (new rectangle(0.7, 0.3)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj10 = new PhyObject(7.5, 3.5, 0.7, 1.5, 20, 0, 0, (new rectangle(0.6, 0.6)), PhyObject::ObjectState::NotFixed);
    PhyObject* obj11 = new PhyObject(5.5, 5.5, 0.7, 1.5, 10, 0, 0, (new rectangle(0.4, 0.4)), PhyObject::ObjectState::NotFixed);
    //PhyObject* obj7 = new PhyObject(12, 2.5, -5, 0, 1, M_PI_4, 0, (new rectangle(0.6, 0.6)), PhyObject::ObjectState::NotFixed);
    //PhyObject* obj = new PhyObject(1000, 350, 0, 0, 20, 10);
    //PhyObject* obj2 = new PhyObject(1036, 330, 0, 0, 20, 10);
    //PhyObject* obj3 = new PhyObject(1036, 370, 0, 0, 20, 10);
    //PhyObject* obj4 = new PhyObject(1072, 310, 0, 0, 20, 10);
    //PhyObject* obj5 = new PhyObject(1072, 350, 0, 0, 20, 10);
    //PhyObject* obj6 = new PhyObject(1072, 390, 0, 0, 20, 10);
    //PhyObject* obj7 = new PhyObject(1108, 290, 0, 0, 20, 10);
    //PhyObject* obj8 = new PhyObject(1108, 330, 0, 0, 20, 10);
    //PhyObject* obj9 = new PhyObject(1108, 370, 0, 0, 20, 10);
    //PhyObject* obj10 = new PhyObject(1108, 410, 0, 0, 20, 10);
    //PhyObject* obj11 = new PhyObject(200, 350, 0.2, 0, 20, 10);
    //this->en->add(obj);
    this->en->add(obj2);
    this->en->add(obj3);
    this->en->add(obj4);
    this->en->add(obj5);
    //this->en->add(obj6);
    this->en->add(obj7);
    this->en->add(obj8);
    this->en->add(obj9);
    this->en->add(obj10);
    this->en->add(obj11);
}

// run() will be called when a thread starts
void QtThread::run()
{
    en->run();
}

void QtThread::runningStateChanged(bool runningState)
{
    emit signalRunningStateChanged(runningState);
}

void QtThread::iterationCompleted()
{
    std::vector<PhyItem*> listofPhyItem;
    std::vector<const PhyObject*> phyobjectlist = (this->en->GetPhyObjects());
    
    
   
    for (int j = 0; j < (int)(phyobjectlist.size()); ++j) {
        if (phyobjectlist[j]->GetShape()->GetShapeType() == baseShape::EnShapeType::Circle)
        {
            PaintCircleItem* CircleItem = new PaintCircleItem();
            CircleItem->locationX = phyobjectlist[j]->GetPositionX();
            CircleItem->locationY = phyobjectlist[j]->GetPositionY();
            CircleItem->Angle = phyobjectlist[j]->GetAngle();
            CircleItem->AngularVelocity = phyobjectlist[j]->GetAngularVelocity();
            const baseShape* shapePointer = phyobjectlist[j]->GetShape();
            const circle* circleShape = dynamic_cast<const circle*>(shapePointer);
            CircleItem->rad = circleShape->GetRadius();
            listofPhyItem.push_back(CircleItem);
        }

        else if (phyobjectlist[j]->GetShape()->GetShapeType() == baseShape::EnShapeType::Rectangle)
        {
            PaintRectangleItem* RectangleItem =new PaintRectangleItem();
            RectangleItem->locationX = phyobjectlist[j]->GetPositionX();
            RectangleItem->locationY = phyobjectlist[j]->GetPositionY();
            RectangleItem->Angle = phyobjectlist[j]->GetAngle();
            RectangleItem->AngularVelocity = phyobjectlist[j]->GetAngularVelocity();
            const baseShape* shapePointer = phyobjectlist[j]->GetShape();
            const rectangle* rectangleShape = dynamic_cast<const rectangle*>(shapePointer);
            RectangleItem->width = rectangleShape->GetWidth();
            RectangleItem->height = rectangleShape->GetHeight();
            listofPhyItem.push_back(RectangleItem);
        }
    }
    emit signalIterationCompleted(listofPhyItem);
}

void QtThread::StartStop()
{
    if (en->GetRunState())
    {
        en->stop();
    }
    else
    {
        this->start();
    }
}
