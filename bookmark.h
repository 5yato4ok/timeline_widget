
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QWidget>
#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsObject>
#include "drawelementwidget.h"

namespace time_line {
/**
 * @brief: draw one bookmark
 */
class Bookmark : public DrawElementWidget {
  Q_OBJECT
public:
  explicit Bookmark(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
protected:
    QString getDescription() override;
    QString getName() override;
    QPalette getPalette() override;
};
} // namespace time_line
#endif // BOOKMARK_H
