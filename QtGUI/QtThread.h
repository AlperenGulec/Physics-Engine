#ifndef QTTHREAD_H
#define QTTHREAD_H

#include <QThread>
#include "engineListener.h"
#include "engine.h"
#include "PhyItem.h"
#include "QtGUIBoard.h"
#include "baseShape.h"
#include "PhyObject.h"
#include "PaintCircleItem.h"
#include "PaintRectangleItem.h"

class QtThread : public QThread, engineListener
{
    Q_OBJECT
public:
    explicit QtThread(QObject* parent = 0, bool b = false);
    void run();

    void runningStateChanged(bool runningState);//Engine listener için
    void iterationCompleted();//Engine listener için
    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;

signals:
    void signalRunningStateChanged(bool runningState);
    void signalIterationCompleted(std::vector<PhyItem*> items);


public slots:
    void StartStop();

private:
    engine* en;
};

#endif // QTTHREAD_H