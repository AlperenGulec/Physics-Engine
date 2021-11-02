#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGUI.h"
#include "engine.h"
#include <thread>
#include "QtThread.h"

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE
class QtGUIBoard;

class QtGUI : public QWidget
{
    Q_OBJECT

public:
    QtGUI(QWidget *parent = Q_NULLPTR);

public slots:
    void OnRunningStateChanged(bool isRunningState);
    void OnIterationCompleted(std::vector<PhyItem*> items);

private:
    QtGUIBoard* board;
    QPushButton* startButton;
    QPushButton* quitButton;
};
