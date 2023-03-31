#include "time_line.h"
#include <QFontMetrics>
namespace time_line {

TimeLine::TimeLine(QMainWindow* parent): QWidget(parent),
    offset(0)
{
    setFixedSize(40, parent->height());
    move(0, 40);
    //connect(parent->verticalScrollBar(), &QScrollBar::valueChanged, this, &TimeLine::setOffset);
}

void TimeLine::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.translate(0, -offset);
    int const heightMM = height() * toMM(painter.device());
    painter.setFont(font());

    QFontMetrics fm(font());
    for (int position = 0; position < heightMM; ++position)
    {
        int const positionInPix = int(position / toMM(painter.device()));
        if (position % 10 == 0)
        {
            if (position != 0)
            {
                QString const txt = QString::number(position);
                QRect txtRect = fm.boundingRect(txt).translated(0, positionInPix);
                txtRect.translate(0, txtRect.height()/2);
                painter.drawText(txtRect, txt);
            }
            painter.drawLine(width() - 15, positionInPix, width(), positionInPix);
        }
        else {
            painter.drawLine(width() - 10, positionInPix, width(), positionInPix);
        }
    }
}


void TimeLine::resizeEvent(QResizeEvent* event)
{
    QPainter painter(this);
    int const maximumMM = event->size().height() * toMM(painter.device());
    QFontMetrics fm(font());
    //QString::number(maximumMM))
    int w = fm.maxWidth() + 20;
    if (w != event->size().width())
    {
        QSize const newSize(w, event->size().height());
        emit sizeChanged(newSize);
        return setFixedSize(newSize);
    }
    return QWidget::resizeEvent(event);
}

void TimeLine::setOffset(int value)
{
    offset = value;
    update();
}

qreal TimeLine::toMM(const QPaintDevice* dev)
{
    return 25.4 / dev->logicalDpiX();
}
}
