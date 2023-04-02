
#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H

#include <QGraphicsView>
#include <QPushButton>
#include <QSpinBox>
#include "time_line.h"
#include "drawobj.h"
#include "bookmark.h"
#include "groupbookmark.h"
namespace time_line {
class ViewHandler : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewHandler(QWidget *parent = 0);
    QGraphicsScene      *scene;
    TimeLine* time_line;
public slots:
    void drawVisibleObjects(const std::vector<DrawObj>&);
signals:
    void hourScaleInPixelsCalculated(int scale);

private:
    const size_t TIME_LINE_POS = 50;
    void drawTimeLine();

};
}
#endif // VIEWHANDLER_H
