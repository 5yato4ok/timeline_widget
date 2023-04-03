
#include "bookmark.h"
#include <QMainWindow>
namespace time_line {

Bookmark::Bookmark(const TimeLineItem &desc, QWidget *parent)
    : DrawElementWidget(desc, parent) {}

QString Bookmark::getDescription() { return getName(); }

QString Bookmark::getName() {
  return "Bookmark " + QString::number(desc_draw.bkmrks_idxs.front());
}

QPalette Bookmark::getPalette() { return palette(); }

} // namespace time_line
