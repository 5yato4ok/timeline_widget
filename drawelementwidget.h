
#ifndef DRAWELEMENTWIDGET_H
#define DRAWELEMENTWIDGET_H

#include <QWidget>
#include <QPalette>
#include "drawobj.h"

namespace time_line {

class DrawElementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawElementWidget(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent * e) override;
signals:
    void needToShowInfo(const QString& desc);
protected:
    virtual QString getDescription() = 0;
    virtual QString getName() = 0;
    virtual QPalette getPalette() = 0;

    DrawWidgetDesc desc_draw;
    double duration_hour;
    QWidget* widgetDesc;
    bool hovering;
};
}
#endif // DRAWELEMENTWIDGET_H
