
#include "viewhandler.h"

namespace time_line {
ViewHandler::ViewHandler(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent");
    setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pushButton = new QPushButton(this);
    pushButton->move(80,0);
    spinBox = new QSpinBox(this);

//      QObject::connect(pushButton, &QPushButton::clicked, gen_handler,
//                       &GenerationHandler::startGeneration);
//      QObject::connect(spinBox, &QSpinBox::valueChanged, gen_handler,
//                       &GenerationHandler::setNumOfBkmrs);
    //this->setMinimumHeight(100);
    //this->setMinimumWidth(100);
    scene = new QGraphicsScene();
    this->setScene(scene);

    time_line = new TimeLine(this);
    time_line->move(0, 150);
    scene->addWidget(spinBox);
    scene->addWidget(pushButton);
    scene->addWidget(time_line);


    //time_line_group = new QGraphicsItemGroup(parent);
    //book_mark_group = new QGraphicsItemGroup(parent);
    //time_line_group->addToGroup();


    //scene->addItem(time_line_group);
    //scene->addItem(book_mark_group);
}

}
