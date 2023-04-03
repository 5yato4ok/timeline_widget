
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
#include <mutex>

namespace time_line {
class ViewHandler : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewHandler(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event) override;
    bool event(QEvent * e) override;
public slots:
    void drawVisibleObjects(const std::vector<DrawObj>&);
    void cacheBkmrks(const PartedStorageOfBkmrks&);
    //void setGenerationStatus(bool);
signals:
    void recalcVisibleObjectRequired(const PartedStorageOfBkmrks&);
    void generationStatusRequied();

private:
    void clearVisibleWidgets();
    std::unordered_map<QObject*, std::shared_ptr<QWidget>> visible_widgets;
    const int TIME_LINE_POS = 30;
    const int OBJS_POS = TIME_LINE_POS + 30;
    void drawTimeLine();
    QGraphicsScene      *scene;
    QGraphicsItemGroup *bkmrk_group;
    TimeLine* time_line;
    bool is_generated_bkmrks;
    PartedStorageOfBkmrks cached_bkmrks;
    std::mutex m;

};
}
#endif // VIEWHANDLER_H
