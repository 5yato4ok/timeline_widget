
#include "bookmark.h"
#include "time_line.h"
namespace time_line {

Bookmark::Bookmark( double start, double duration_, size_t pos, QWidget *parent)
    : QWidget{parent}, start_hour(start), idx(pos),
      duration_hour(duration_) {
  name = "Bookmark " + QString::number(idx);
  setMinimumHeight(20);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  move(23 * start_hour, 0);
}
double Bookmark::getStartPos() { return start_hour; }

void Bookmark::paint_by_pos(double curScale, int pos_y)
{
    int width =  curScale * duration_hour;
    setFixedWidth(curScale * duration_hour);
    move(curScale * start_hour, pos_y);
    //update();
    repaint();
}

void Bookmark::resizeEvent(QResizeEvent *event) {
    int smth = 2;
}

bool Bookmark::event(QEvent* evt)
{
    auto event_type = evt->type();

    return QWidget::event(evt);
}

//void Bookmark::paintEvent(QPaintEvent *event) {
//  QPainter painter{this};
//  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//  QLinearGradient bg_gradient(rect().topLeft(), rect().bottomLeft());
//  bg_gradient.setColorAt(0, palette().button().color().lighter());
//  bg_gradient.setColorAt(1, palette().button().color());
//  painter.setBrush(QBrush{bg_gradient});
//  painter.setPen(QPen{palette().buttonText(), 1});
//  painter.drawRoundedRect(rect(), 5, 5);
//  painter.setBrush(Qt::NoBrush);
//  painter.setPen(QPen{palette().buttonText(), 1});
//  QFont font;
//  font.setPixelSize(8);


//  QRect text_rect = rect().adjusted(5, 5, -5, -5);
//  painter.setFont(font);
//  painter.drawText(text_rect, Qt::AlignCenter,
//                   painter.fontMetrics().elidedText(
//                       name, Qt::TextElideMode::ElideRight, text_rect.width()));
//  QWidget::paintEvent(event);
//}
} // namespace time_line
