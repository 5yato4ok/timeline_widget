
#include "generationhandler.h"

namespace time_line {
GenerationHandler::GenerationHandler(QLayout *layout, QWidget *parent)
    : QWidget{parent}, num_of_bkmrs(0), bkmrks_layout(layout) {
}
void GenerationHandler::startGeneration() {
  clearLayout();
  bkmrk_storage_parted.clear();
  group_bkmrk_storage_parted.clear();
  if (num_of_bkmrs == 0)
    return;
  generateBkmrks();
  generateGroups();
};

void GenerationHandler::clearLayout() {
  foreach (QObject *object, bkmrks_layout->children()) {
    QWidget *widget = qobject_cast<QWidget *>(object);
    if (widget) {
      bkmrks_layout->removeWidget(widget);
    }
  }
}

void GenerationHandler::generateBkmrks() {
  auto bkm = new Bookmark(0, 2, 0,this);
  auto y = bkmrks_layout->geometry().top();
  bkm->paint_by_pos(TimeLine::getHourScale(bkmrks_layout->parentWidget()->rect()),y);
  //bkm->update();
  //bkmrks_layout->addWidget(bkm);

  auto bkm2 = new Bookmark(1, 1.5, 1,this);
  bkm2->paint_by_pos(TimeLine::getHourScale(bkmrks_layout->parentWidget()->rect()),y);
  //bkm->update();
  //bkmrks_layout->addWidget(bkm2);

  auto bkm3 = new Bookmark(3, 2.5, 2,this);
  bkm3->paint_by_pos(TimeLine::getHourScale(bkmrks_layout->parentWidget()->rect()),y);
  //bkm->update();
  //bkmrks_layout->addWidget(bkm3);
}

void GenerationHandler::generateGroups(){};

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
}
} // namespace time_line
