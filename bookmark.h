
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QWidget>
#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsObject>

namespace time_line {
/**
 * @brief: draw one bookmark
 */
class Bookmark : public QWidget {
  Q_OBJECT
public:
  explicit Bookmark(double start_hour, double end_hour, size_t idx,int y, double scale, QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event) override;

private:
  double start_hour;
  double cur_scale;
  double duration_hour;
  int y_pos;
  QString name;
};
} // namespace time_line
#endif // BOOKMARK_H
