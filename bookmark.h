
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QWidget>
#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsObject>
#include "drawobj.h"

namespace time_line {
/**
 * @brief: draw one bookmark
 */
class Bookmark : public QWidget {
  Q_OBJECT
public:
  explicit Bookmark(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event) override;

private:
  DrawWidgetDesc desc_draw;
  double duration_hour;
  QString name;
};
} // namespace time_line
#endif // BOOKMARK_H
