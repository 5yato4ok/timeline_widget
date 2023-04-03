
#ifndef DRAWELEMENTWIDGET_H
#define DRAWELEMENTWIDGET_H

#include <QWidget>
#include <QPalette>
#include "timelineitem.h"

namespace time_line {

class DrawElementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawElementWidget(const TimeLineItem& desc, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
protected:
    virtual QString getDescription() = 0;
    virtual QString getName() = 0;
    virtual QPalette getPalette() = 0;

    TimeLineItem desc_draw;
    double duration_hour;
    QWidget* widgetDesc;
};
}
#endif // DRAWELEMENTWIDGET_H
