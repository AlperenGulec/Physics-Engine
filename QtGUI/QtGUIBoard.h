#pragma once
#include <QFrame>
#include "QtGUI.h"
#include "PhyItem.h"

class QtGUIBoard : public QFrame
{
	Q_OBJECT

public:
	QtGUIBoard(QWidget* parent = nullptr);

public slots:
	void ClearItems();
	void AddItem(PhyItem& item);
	void setStartValue(bool isStarted); //SetStartValue(bool isStarted)
	void SetItems(std::vector<PhyItem*> items);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	std::vector<PhyItem*> ItemList;
	enum { BoardWidth = 10, BoardHeight = 22 };

	void drawCircle(QPainter& painter, QRectF rectangle);

	bool isStarted;
};

