
#ifndef TIME_LINE_H
#define TIME_LINE_H
#include <QAbstractScrollArea>
#include <QMainWindow>
#include <QPainter>
#include <QResizeEvent>
#include <QScrollBar>
#include <QWidget>

namespace time_line {
/**
 * @brief draws time_stamps of timeline on start and on change of window size
 */
class TimeLine : public QWidget {
  Q_OBJECT
public:
  TimeLine(QWidget *parent = nullptr);
  virtual void paintEvent(QPaintEvent *event) override;
  static double getHourScale(const QRect &rect) {
    return rect.bottomRight().rx() / 23;
  }

  static double getMilliSecScale(const QRect &rect) {
    return double(rect.bottomRight().rx()) / 23 / 60 / 60 / 60;
  }

  static int getMilliSecPerPixel(double scale) { return 1 / scale; }

private:
  QString prettify(int seconds) const;
};

} // namespace time_line
#endif // TIME_LINE_H
