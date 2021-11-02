#include "QtGUI.h"
#include <QtWidgets/QApplication>
#include <math.h>

int main(int argc, char *argv[])
{
    point p2 = point(5, 5);
    point p1 = point(8, 5);
    point p3 = point(10, 0);
    line l = line(p1, p2);
    double d = l.pointToLineDistance(p3);

    QApplication a(argc, argv);
    QtGUI w;
    w.showMaximized();
    return a.exec();
}
