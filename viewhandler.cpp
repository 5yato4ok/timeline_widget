
#include "viewhandler.h"
#include <QGraphicsProxyWidget>

namespace time_line {
using namespace std;
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
    emit sizeChanged();
    return QWidget::resizeEvent(evt);
}

void ViewHandler::drawVisibleObjects(const std::vector<DrawObj>& objs) {
    clearVisibleWidgets();
    int cur_group_count = 0;
    auto curScale = TimeLine::getHourScale(rect());
    for(auto& obj: objs) {
        shared_ptr<QWidget> ptr;
        if (obj.isGroupObj()) {
            ptr = make_shared<GroupBookMark>(nullptr);
        } else {
            ptr = make_shared<Bookmark>(obj.start_hour, obj.end_hour,
                                        obj.bkmrks_idxs.front(),OBJS_POS, curScale, nullptr);
        }

        scene->addWidget(ptr.get());
        visible_widgets[ptr.get()] = ptr;
    }
    scene->update();
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
