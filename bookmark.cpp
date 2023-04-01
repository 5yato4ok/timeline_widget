
#include "bookmark.h"
namespace time_line {

Bookmark::Bookmark(QWidget *parent) : QWidget{parent} {}
size_t Bookmark::getStart() { return start_pixel; }
} // namespace time_line
