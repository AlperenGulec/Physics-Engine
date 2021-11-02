#include "QtGUI.h"
#include "QtGUIBoard.h"
#include <QPushButton>
#include <QCoreApplication>
#include <QGridLayout>
#include "engineListener.h"
#include "engine.h"

QtGUI::QtGUI(QWidget *parent)
    : QWidget(parent), board(new QtGUIBoard)
{
    QtThread* otherThread = new QtThread;

    startButton = new QPushButton(tr("&Start"));
    startButton->setCheckable(true);
    startButton->setFocusPolicy(Qt::NoFocus);
    
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, otherThread, &QtThread::StartStop);
    connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(otherThread, SIGNAL(signalRunningStateChanged(bool)), this, SLOT(OnRunningStateChanged(bool)));
    connect(otherThread, SIGNAL(signalIterationCompleted(std::vector<PhyItem*>)), this, SLOT(OnIterationCompleted(std::vector<PhyItem*>)));

    QGridLayout* layout = new QGridLayout;
    
    layout->addWidget(startButton, 1, 0);
    layout->addWidget(board, 2, 0);
    layout->addWidget(quitButton, 3, 0);
    setLayout(layout);
    
    setWindowTitle(tr("Physics Engine"));
    resize(550,370); //550,370
}

void QtGUI::OnRunningStateChanged(bool runningState)
{
    this->board->setStartValue(runningState);
    startButton->setText(startButton->isChecked() ? "Stop" : "Play");
    this->board->update();
}

void QtGUI::OnIterationCompleted(std::vector<PhyItem*> items)
{
    this->board->SetItems(items);
    this->board->update();
}
