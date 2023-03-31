
#ifndef TIME_LINE_H
#define TIME_LINE_H
#include <QWidget>
#include <QPainter>
#include <QScrollBar>
#include <QMainWindow>
#include <QAbstractScrollArea>
#include <QResizeEvent>

namespace time_line {

class TimeLine: public QWidget
{
    Q_OBJECT
public:
    TimeLine(QMainWindow* parent=nullptr);
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

    void setOffset(int value);
signals:
    void sizeChanged(QSize const&);
private:
    int offset;

    qreal toMM(const QPaintDevice* dev);
};

}
#endif // TIME_LINE_H
