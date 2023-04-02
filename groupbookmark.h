
#ifndef GROUPBOOKMARK_H
#define GROUPBOOKMARK_H

#include <QWidget>
#include "drawobj.h"
#include <vector>

namespace time_line {
/**
 * @brief draws one group of bookmarks
 */
class GroupBookMark : public QWidget {
  Q_OBJECT
public:
  explicit GroupBookMark(const DrawWidgetDesc& desc, QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event) override;
private:
  DrawWidgetDesc desc_draw;
  double duration_hour;
  QString name;
};
} // namespace time_line

#endif // GROUPBOOKMARK_H
