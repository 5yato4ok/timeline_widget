
#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H

#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsItemGroup>
#include <QSpinBox>
#include "time_line.h"
#include "drawobj.h"
#include "bookmark.h"
#include "groupbookmark.h"
#include <utility>
#include <unordered_set>

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
    std::unordered_map<QObject*, std::shared_ptr<QWidget>> visible_widgets;
    const size_t TIME_LINE_POS = 50;
    const size_t OBJS_POS = TIME_LINE_POS + 30;
    void drawTimeLine();
    QGraphicsScene      *scene;
    QGraphicsItemGroup *bkmrk_group;
    TimeLine* time_line;

};
}
#endif // VIEWHANDLER_H
