
#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H

#include <QGraphicsView>
#include <QPushButton>
#include <QSpinBox>
#include "time_line.h"
#include "drawobj.h"
#include "bookmark.h"
#include "groupbookmark.h"
#include <utility>

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
    void sizeChanged();

private:
    void clearVisibleWidgets();
    std::vector<std::shared_pointer<QWidget>> visible_widgets;
    const size_t TIME_LINE_POS = 50;
    const size_t OBJS_POS = TIME_LINE_POS + 10;
    void drawTimeLine();
    QGraphicsScene      *scene;
    TimeLine* time_line;

};
}
#endif // VIEWHANDLER_H
