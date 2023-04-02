#include "time_line.h"
#include <QFontMetrics>
#include <exception>
namespace time_line {

TimeLine::TimeLine(QWidget *parent) : QWidget(parent) {
  setFixedHeight(30);
  //setFixedWidth(parent!=nullptr? parent->width() : 80);
  //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void TimeLine::paintEvent(QPaintEvent *evt) {
  setFixedWidth(parentWidget()->width());
  QPainter painter{this};
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
  QLinearGradient gradient(evt->rect().topLeft(), evt->rect().bottomLeft());
  gradient.setColorAt(0, palette().window().color());
  gradient.setColorAt(1, palette().window().color().darker());
  painter.setBrush(QBrush{gradient});
  painter.setPen(Qt::NoPen);
  painter.drawRect(evt->rect());
  painter.setPen(QPen{palette().buttonText().color(), 2});
  painter.drawLine(evt->rect().bottomLeft(), evt->rect().bottomRight());
  painter.setPen(palette().buttonText().color());
  auto _visualScale = TimeLine::getHourScale(evt->rect());

  const int shown_hours = 23;
  for (int first_line = 0; first_line <= shown_hours; ++first_line) {
    QString time_string{prettify(first_line)};
    painter.drawText(QPointF{first_line * _visualScale -
                                 painter.fontMetrics()
                                         .size(Qt::TextSingleLine, time_string)
                                         .width() /
                                     2.0,
                             10},
                     time_string);
    painter.drawLine(first_line * _visualScale, 20, first_line * _visualScale,
                     30);
  }

  return QWidget::paintEvent(evt);
}

QString TimeLine::prettify(int hours) const {
  QString result{"%1h"};
  return result.arg(hours, 2, 10);
}
} // namespace time_line
