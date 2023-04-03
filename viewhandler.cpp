
#include "viewhandler.h"
#include <QGraphicsProxyWidget>
#include <utility>

namespace time_line {

ViewHandler::ViewHandler(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background: transparent");
    setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    time_line = new TimeLine(nullptr);
    time_line->move(0, TIME_LINE_POS);
    scene->addWidget(time_line);

}

void ViewHandler::resizeEvent(QResizeEvent *evt) {
    time_line->setFixedWidth(width());
    if(!cached_bkmrks.empty())
        emit recalcVisibleObjectRequired(cached_bkmrks);
    return QWidget::resizeEvent(evt);
}

void ViewHandler::drawVisibleObjects(const std::vector<TimeLineItem>& objs) {
    clearVisibleWidgets();
    int cur_group_count = 0;
    auto curScale = TimeLine::getHourScale(rect());
    for(auto& obj: objs) {
        std::shared_ptr<QWidget> ptr;
        TimeLineItem desc = {obj.start_sec, obj.end_sec,
                               obj.bkmrks_idxs,OBJS_POS, curScale};
        if (obj.isGroupObj()) {
            ptr = std::make_shared<GroupBookMark>(desc, nullptr);
        } else {
            ptr = std::make_shared<Bookmark>(desc, nullptr);
        }

        scene->addWidget(ptr.get());
        visible_widgets[ptr.get()] = ptr;
    }
    scene->update();
}
void ViewHandler::cacheBkmrks() {
    m.lock();
    cached_bkmrks.clear();
    emit cacheRequested(cached_bkmrks);
    m.unlock();
    emit recalcVisibleObjectRequired(cached_bkmrks);
}

void ViewHandler::clearVisibleWidgets() {
    for(auto& item: scene->items()) {
        if (visible_widgets.find(item->toGraphicsObject())!= visible_widgets.end()){
            scene->removeItem(item);
        }
    }
    visible_widgets.clear();
}
}
