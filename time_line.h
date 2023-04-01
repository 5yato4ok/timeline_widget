
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
 * @brief draws time_stamps on start and on change of window size
 */
class TimeLine : public QWidget {
  Q_OBJECT
public:
  TimeLine(QMainWindow *parent);
  virtual void paintEvent(QPaintEvent *event) override;

private:
  QString prettify(int seconds) const;
};

} // namespace time_line
#endif // TIME_LINE_H
