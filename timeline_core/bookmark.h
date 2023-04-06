
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "drawelementwidget.h"
#include <QGraphicsObject>
#include <QLinearGradient>
#include <QPainter>
#include <QWidget>

namespace time_line {
/**
 * @brief: draw one bookmark
 */
class Bookmark : public DrawElementWidget {
  Q_OBJECT
public:
  explicit Bookmark(const TimeLineItem &desc, QWidget *parent = nullptr);

protected:
  QString getDescription() override;
  QString getName() override;
  QPalette getPalette() override;
};
} // namespace time_line
#endif // BOOKMARK_H
