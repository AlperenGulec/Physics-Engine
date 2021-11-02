#include "QtGUIBoard.h"
#include "QtGUI.h"
#include <QPainter>
#include <QLabel>
#include <QPaintEvent>

QtGUIBoard::QtGUIBoard(QWidget* parent)
    : QFrame(parent), isStarted(false)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
}
void QtGUIBoard::ClearItems()
{
    ItemList.clear();
}

void QtGUIBoard::SetItems(std::vector<PhyItem*> items)
{
    //Bütün objelerin silinmesi gerekiyor.
    for (int i = 0; i < ItemList.size(); ++i) {
        delete this->ItemList[i];
    }
    //this->ItemList.clear();
    this->ItemList = items;
}

void QtGUIBoard::AddItem(PhyItem& item)
{
    ItemList.push_back(&item);
}


void QtGUIBoard::setStartValue(bool isStarted)
{
    this->isStarted = isStarted;
}

void QtGUIBoard::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(Qt::transparent);
    QPen p;
    p.setColor ( Qt::black);
    p.setWidth(2);

    painter.setPen(p);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);

    if (isStarted) {
        for (int m = 0; m < this->ItemList.size(); ++m) {
            ItemList[m]->PaintItem(painter);
        }
    }

    else if (!isStarted) {
        for (int m = 0; m < this->ItemList.size(); ++m) {
            ItemList[m]->PaintItem(painter);
        }
        painter.drawText(rect(), Qt::AlignCenter, tr("Stoped"));
    }
    
}

void QtGUIBoard::drawCircle(QPainter& painter, QRectF rectangle)
{
    painter.drawEllipse(rectangle);
}
