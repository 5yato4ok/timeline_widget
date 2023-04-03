
#ifndef DRAWELEMENTWIDGET_H
#define DRAWELEMENTWIDGET_H

#include <QWidget>
#include <QPalette>
#include "drawobj.h"

namespace time_line {

class DrawElementWidgetDesc : public QWidget
{
    Q_OBJECT
public:
    explicit DrawElementWidgetDesc(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void setDesc(const QString &);
private:
    int getDescWidth(const QPainter& painter);
    const DrawWidgetDesc& desc_draw;
    QString desc;
};

class DrawElementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawElementWidget(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent * e) override;
protected:
    virtual QString generateDescription() = 0;
    virtual QString getName() = 0;
    virtual QPalette getPalette() = 0;

    DrawWidgetDesc desc_draw;
    DrawElementWidgetDesc* desc_draw_widget;
    double duration_hour;
    QWidget* widgetDesc;
    bool hovering;
};
}
#endif // DRAWELEMENTWIDGET_H
