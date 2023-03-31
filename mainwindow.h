
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QGraphicsView>
#include "time_line.h"
#include "bookmark.h"
#include "groupbookmark.h"
#include "board.h"
#include "ui_mainwindow.h"

namespace time_line{
class GraphicsView: public QMainWindow
{
public:
    GraphicsView(QWidget* parent=nullptr): QMainWindow(parent),
        ruler(new TimeLine(this))
    {
        ui->setupUi(this);
        //connect(ruler, &TimeLine::sizeChanged, [this](QSize const& size) { setViewportMargins(size.width(), size.width(), 0, 0); });
    }

    ~GraphicsView() {
        delete ui;
    }

//    void setScene(QGraphicsScene* scene)
//    {
//        QGraphicsView::setScene(scene);
//        if (scene)
//            ruler->setFixedHeight(scene->height());
//    }
private:
    TimeLine* ruler;
    Ui::MainWindow *ui;
};
}
#endif // MAINWINDOW_H
