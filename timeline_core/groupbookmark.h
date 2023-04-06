
#ifndef GROUPBOOKMARK_H
#define GROUPBOOKMARK_H

#include <QWidget>
#include "drawelementwidget.h"
#include <vector>

namespace time_line {
/**
 * @brief draws one group of bookmarks
 */
class GroupBookMark : public DrawElementWidget {
  Q_OBJECT
public:
  explicit GroupBookMark(const TimeLineItem& desc, QWidget *parent = nullptr);
  QString getDescription() override;
  QString getName() override;
  QPalette getPalette() override;
};
} // namespace time_line

#endif // GROUPBOOKMARK_H
