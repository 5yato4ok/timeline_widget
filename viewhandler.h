
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
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void drawVisibleObjects(const std::vector<DrawObj>&);
signals:
    void sizeChange();

private:
    const size_t TIME_LINE_POS = 50;
    void drawTimeLine();
    QGraphicsScene      *scene;
    TimeLine* time_line;

};
}
#endif // VIEWHANDLER_H
