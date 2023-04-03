
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

    //desc_draw_widget = new DrawElementWidgetDesc(desc_draw, this);
    //desc_draw_widget->move(desc_draw.scale * desc_draw.start_hour, desc_draw.y);
    //desc_draw_widget->setAttribute(Qt::WA_TransparentForMouseEvents);

}

void DrawElementWidget::paintEvent(QPaintEvent *event) {
    auto usedPallete = getPalette();
//    setFixedWidth(desc_draw.scale * duration_hour);
//    move(desc_draw.scale * desc_draw.start_hour, desc_draw.y);
//    desc_draw_widget->setVisible(hovering);
//    desc_draw_widget->move(desc_draw.scale * desc_draw.start_hour, desc_draw.y);
//    desc_draw_widget->setPalette(usedPallete);

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
    if (hovering) {
        //desc_draw_widget->repaint();
    }

    QWidget::paintEvent(event);
}

int DrawElementWidgetDesc::getDescWidth(const QPainter& painter) {
    QString averagePhrase = "Bookmark 1";
    return painter.fontMetrics().averageCharWidth() * 20;
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

DrawElementWidgetDesc::DrawElementWidgetDesc(const DrawWidgetDesc& desc, QWidget *parent):
    QWidget(parent), desc_draw(desc) {}
void DrawElementWidgetDesc::setDesc(const QString &s) {
    desc = s;
}

void DrawElementWidgetDesc::paintEvent(QPaintEvent *event) {
//    move(desc_draw.scale * desc_draw.start_hour, desc_draw.y+10);
//    QPainter p_hovering{this};
//    auto textWidth = std::max(getDescWidth(p_hovering),width());
//    setFixedWidth(textWidth + 5);

//    p_hovering.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//    auto clr1 = palette().button().color();
//    clr1.setAlpha(200);
//    auto clr2 = palette().button().color();
//    clr2.setAlpha(200);

//    QLinearGradient bg_gradient(rect().topLeft(), rect().bottomLeft());
//    bg_gradient.setColorAt(0, clr1);
//    bg_gradient.setColorAt(1, clr2);

//    p_hovering.setBrush(QBrush{bg_gradient});
//    p_hovering.setPen(QPen{palette().buttonText(), 1});
//    p_hovering.drawRoundedRect(rect(), 5, 5);

//    p_hovering.setBrush(Qt::NoBrush);
//    QRect text_rect = rect().adjusted(5, 5, -5, -5);
//    QFont font;
//    font.setPixelSize(8);
//    p_hovering.setFont(font);
//    p_hovering.drawText(text_rect, Qt::AlignCenter,
//                        p_hovering.fontMetrics().elidedText(
//                            desc, Qt::TextElideMode::ElideRight, text_rect.width()));
//    QWidget::paintEvent(event);
}
} // namespace time_line
