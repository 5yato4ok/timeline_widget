
#include "drawelementwidget.h"
#include <QPainter>
#include <QEvent>

namespace time_line {

DrawElementWidget::DrawElementWidget(const DrawWidgetDesc& desc, QWidget *parent)
    : QWidget{parent}, desc_draw(desc),hovering(false),
    duration_hour(abs(desc.end_hour - desc.start_hour)) {
    setFixedHeight(20);
    setFixedWidth(desc_draw.scale * duration_hour);
    move(desc_draw.scale * desc_draw.start_hour, desc_draw.y);

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


bool DrawElementWidget::event(QEvent * evt)
{
    switch (evt->type())
    {
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    {
        if ((evt->type() == QEvent::HoverEnter) != hovering)
        {
            update(rect());
            hovering = evt->type() == QEvent::HoverEnter;
        }
        return true;
    }
    }

    return QWidget::event(evt);
}

} // namespace time_line
