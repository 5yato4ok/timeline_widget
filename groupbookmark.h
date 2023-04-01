
#ifndef GROUPBOOKMARK_H
#define GROUPBOOKMARK_H

#include <QWidget>

namespace time_line {
/**
 * @brief draws one group of bookmarks
 */
class GroupBookMark : public QWidget {
  Q_OBJECT
public:
  explicit GroupBookMark(QWidget *parent = nullptr);

signals:
};
} // namespace time_line

#endif // GROUPBOOKMARK_H
