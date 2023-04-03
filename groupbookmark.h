
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
  explicit GroupBookMark(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
protected:
  QString getDescription() override;
  QString getName() override;
  QPalette getPalette() override;
};
} // namespace time_line

#endif // GROUPBOOKMARK_H
