
#include "drawelementwidget.h"
#include <QPainter>
#include <QEvent>

namespace time_line {

DrawElementWidget::DrawElementWidget(const TimeLineItem& desc, QWidget *parent)
    : QWidget{parent}, desc_draw(desc) {
    duration_hour = abs(desc.end_sec - desc.start_sec)/60/60;
    setFixedHeight(20);
    setFixedWidth(desc_draw.hour_scale * duration_hour);
    move(desc_draw.hour_scale * (desc_draw.start_sec/60/60), desc_draw.y);

    setAttribute(Qt::WA_Hover);
}

void DrawElementWidget::paintEvent(QPaintEvent *event) {
    setToolTip(getDescription());
    auto usedPallete = getPalette();
    QPainter painter{this};
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setBrush(usedPallete.button().color());
    painter.setPen(QPen{usedPallete.buttonText(), 1});
    painter.drawRoundedRect(rect(), 5, 5);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen{usedPallete.buttonText(), 1});
    QFont font;
    font.setPixelSize(8);

    QRect text_rect = rect().adjusted(5, 5, -5, -5);
    painter.setFont(font);
    painter.drawText(text_rect, Qt::AlignCenter,
                     painter.fontMetrics().elidedText(
                         getName(), Qt::TextElideMode::ElideRight, text_rect.width()));

    QWidget::paintEvent(event);
}

} // namespace time_line
