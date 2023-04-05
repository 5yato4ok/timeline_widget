
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
 * @brief controls gui representation of generated data
 */
class ViewHandler : public QGraphicsView {
  Q_OBJECT
public:
  explicit ViewHandler(QWidget *parent = 0);
  void resizeEvent(QResizeEvent *event) override;
public slots:
  void drawVisibleObjects(const VisibleObjs &);
signals:
  void recalcVisibleObjectRequired();

private:
  void clearVisibleWidgets();
  std::unordered_map<QObject *, std::shared_ptr<QWidget>> visible_widgets;
  const int TIME_LINE_POS = 0;
  const int OBJS_POS = TIME_LINE_POS + 30;
  QGraphicsScene *scene;
  QGraphicsItemGroup *bkmrk_group;
  TimeLine *time_line;
};
} // namespace time_line
#endif // VIEWHANDLER_H
