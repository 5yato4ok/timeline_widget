
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    using namespace time_line;
    QApplication a(argc, argv);
    GraphicsView w;
    w.show();
    return a.exec();
}
