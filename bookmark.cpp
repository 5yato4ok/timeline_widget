
#include "bookmark.h"
#include "time_line.h"
#include <QMainWindow>
namespace time_line {

Bookmark::Bookmark( double start, double end, size_t idx,int y, double scale, QWidget *parent)
    : QWidget{parent}, start_hour(start),
    duration_hour(abs(end - start)),y_pos(y),
    cur_scale(scale)
{
  name = "Bookmark " + QString::number(idx);
  setFixedHeight(20);
  auto curScale = TimeLine::getHourScale(window()->rect());
  setFixedWidth(curScale * duration_hour);
  move(curScale * start_hour, y_pos);
}


void Bookmark::paintEvent(QPaintEvent *event) {
  //auto curScale = TimeLine::getHourScale(window()->geometry());
  setFixedWidth(cur_scale * duration_hour);
  move(cur_scale * start_hour, y_pos);

  QPainter painter{this};
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
  QLinearGradient bg_gradient(rect().topLeft(), rect().bottomLeft());
  bg_gradient.setColorAt(0, palette().button().color().lighter());
  bg_gradient.setColorAt(1, palette().button().color());
  painter.setBrush(QBrush{bg_gradient});
  painter.setPen(QPen{palette().buttonText(), 1});
  painter.drawRoundedRect(rect(), 5, 5);
  painter.setBrush(Qt::NoBrush);
  painter.setPen(QPen{palette().buttonText(), 1});
  QFont font;
  font.setPixelSize(8);


  QRect text_rect = rect().adjusted(5, 5, -5, -5);
  painter.setFont(font);
  painter.drawText(text_rect, Qt::AlignCenter,
                   painter.fontMetrics().elidedText(
                       name, Qt::TextElideMode::ElideRight, text_rect.width()));
  QWidget::paintEvent(event);
}
} // namespace time_line
