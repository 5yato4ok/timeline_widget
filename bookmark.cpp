
#include "bookmark.h"
#include "time_line.h"
#include <QMainWindow>
namespace time_line {

Bookmark::Bookmark( const DrawWidgetDesc& desc, QWidget *parent)
    : QWidget{parent}, desc_draw(desc), duration_hour(abs(desc.end_hour - desc.start_hour))
{
  name = "Bookmark " + QString::number(desc.idxs.front());
  setFixedHeight(20);
  setFixedWidth(desc_draw.scale * duration_hour);
  move(desc_draw.scale * desc_draw.start_hour, desc_draw.y);
}


void Bookmark::paintEvent(QPaintEvent *event) {
  //auto curScale = TimeLine::getHourScale(window()->geometry());
  setFixedWidth(desc_draw.scale * duration_hour);
  move(desc_draw.scale * desc_draw.start_hour, desc_draw.y);

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
