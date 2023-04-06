
#ifndef DRAWELEMENTWIDGET_H
#define DRAWELEMENTWIDGET_H

#include "timelineitem.h"
#include <QPalette>
#include <QWidget>

namespace time_line {
/**
 * @brief base class of timeline items.
 * sets pallete, tooltip and draws rectangles of required size
 */
class DrawElementWidget : public QWidget {
  Q_OBJECT
public:
  explicit DrawElementWidget(const TimeLineItem &desc,
                             QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event) override;

protected:
  virtual QString getDescription() = 0;
  virtual QString getName() = 0;
  virtual QPalette getPalette() = 0;

  TimeLineItem desc_draw;
  int duration_sec;
  int sec_per_pixel;
  QWidget *widgetDesc;
};
} // namespace time_line
#endif // DRAWELEMENTWIDGET_H
