
#include "bookmark.h"
#include "time_line.h"
#include <QMainWindow>
namespace time_line {

Bookmark::Bookmark( const DrawWidgetDesc& desc, QWidget *parent)
    : DrawElementWidget(desc,parent){}

QString Bookmark::generateDescription() {
  return getName();
}

QString Bookmark::getName() {
  return "Bookmark " + QString::number(desc_draw.idxs.front());
}

QPalette Bookmark::getPalette() {
  return palette();
}

} // namespace time_line
