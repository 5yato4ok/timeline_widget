
#include "viewhandler.h"

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

    time_line = new TimeLine(this);
    time_line->move(0, TIME_LINE_POS);
    scene->addWidget(time_line);

}

void ViewHandler::resizeEvent(QResizeEvent *evt) {
    emit sizeChanged();
    return QWidget::resizeEvent(evt);
}

void ViewHandler::drawVisibleObjects(const std::vector<DrawObj>& objs) {
    clearVisibleWidgets();
    int cur_group_count = 0;
    for(auto& obj: objs) {
        auto ptr = obj.isGroupObj() ? make_shared<GroupBookMark>(0) :
                       make_shared<Bookmark>(obj.start_hour,obj.end_hour,obj.bkmrks_idxs.front(),OBJS_POS);
        scene->addWidget(ptr.get());
        visible_widgets.push_back(ptr);
    }
    repaint();
}

void ViewHandler::clearVisibleWidgets() {
    for(auto& wdgt: visible_widgets) {
        scene->removeItem(wdgt->graphicsProxyWidget());
    }
    visible_widgets.clear();
}
}
