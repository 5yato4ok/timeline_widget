
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QWidget>
#include <QPainter>
#include <QLinearGradient>
#include <QGraphicsObject>

namespace time_line {
/**
 * @brief: draw and hide one bookmark
 */
class Bookmark : public QWidget {
  Q_OBJECT
public:
  explicit Bookmark(double start_hour, double duration_hour, size_t idx, QWidget *parent = nullptr);
  double getStartPos();
  //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
  void paint_by_pos(double curScale, int pos_y);
  void resizeEvent(QResizeEvent *event);
  protected:
  virtual bool event(QEvent* evt);

private:
  double start_hour;
  double duration_hour;
  size_t idx;
  QString name;
};
} // namespace time_line
#endif // BOOKMARK_H
