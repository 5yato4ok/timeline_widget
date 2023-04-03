
#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include "time_line.h"
#include "timelineitem.h"
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QPushButton>
#include <QSpinBox>
#include <mutex>
#include <utility>

namespace time_line {
/**
 * @brief controls gui representation of generated data,
 * stores generated data for recalculation on events
 */
class ViewHandler : public QGraphicsView {
  Q_OBJECT
public:
  explicit ViewHandler(QWidget *parent = 0);
  void resizeEvent(QResizeEvent *event) override;
public slots:
  void drawVisibleObjects(const std::vector<TimeLineItem> &);
  void cacheBkmrks();
signals:
  void recalcVisibleObjectRequired(const PartedStorageOfBkmrks &);
  void cacheRequested(PartedStorageOfBkmrks &);

private:
  void clearVisibleWidgets();
  std::unordered_map<QObject *, std::shared_ptr<QWidget>> visible_widgets;
  const int TIME_LINE_POS = 30;
  const int OBJS_POS = TIME_LINE_POS + 30;
  QGraphicsScene *scene;
  QGraphicsItemGroup *bkmrk_group;
  TimeLine *time_line;
  PartedStorageOfBkmrks cached_bkmrks;
  std::mutex m;
};
} // namespace time_line
#endif // VIEWHANDLER_H
