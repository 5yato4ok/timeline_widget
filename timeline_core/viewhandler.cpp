
#include "viewhandler.h"
#include <QGraphicsProxyWidget>
#include <utility>

namespace time_line {

ViewHandler::ViewHandler(QWidget *parent): QGraphicsView(parent),
    time_line(nullptr) {
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setStyleSheet("background: transparent");
  setAlignment(Qt::AlignCenter);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setMinimumHeight(100);
  this->setMinimumWidth(100);
  scene = new QGraphicsScene(this);
  this->setScene(scene);

  time_line.move(0, TIME_LINE_POS);
  scene->addWidget(&time_line);
}

void ViewHandler::resizeEvent(QResizeEvent *evt) {
  time_line.move(0, TIME_LINE_POS);
  time_line.setFixedWidth(width());
  emit recalcVisibleObjectRequired();
  return QWidget::resizeEvent(evt);
}

ViewHandler::VisibleWidgetsStorage ViewHandler::get_visible_widgets() {
  return visible_widgets;
}

void ViewHandler::drawVisibleObjects(const VisibleObjs &objs) {
  clearVisibleWidgets();
  auto curScale = TimeLine::getMilliSecScale(rect());
  for (auto &obj : objs) {
    std::shared_ptr<QWidget> ptr;
      TimeLineItem desc = {obj.start_millisec, obj.end_millisec, obj.bkmrks_idxs, OBJS_POS,
                         curScale};
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

void ViewHandler::clearVisibleWidgets() {
  for (auto &item : scene->items()) {
    if (visible_widgets.find(item->toGraphicsObject()) !=
        visible_widgets.end()) {
      scene->removeItem(item);
    }
  }
  visible_widgets.clear();
}
} // namespace time_line
