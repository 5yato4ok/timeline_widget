
#include "viewhandler.h"

namespace time_line {
ViewHandler::ViewHandler(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent");
    setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    time_line = new TimeLine(this);
    time_line->move(0, 50);
    scene->addWidget(time_line);
}

}
