
#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H

#include <QGraphicsView>
#include <QPushButton>
#include <QSpinBox>
#include "time_line.h"
#include "bookmark.h"
#include "groupbookmark.h"
namespace time_line {
class ViewHandler : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewHandler(QWidget *parent = 0);
    QGraphicsScene      *scene;
    QPushButton *pushButton;
    QSpinBox *spinBox;
    TimeLine* time_line;

private:
    void drawTimeLine();

};
}
#endif // VIEWHANDLER_H
