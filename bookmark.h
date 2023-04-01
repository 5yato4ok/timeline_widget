
#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QWidget>

namespace time_line {
/**
 * @brief: draw and hide one bookmark
 */
class Bookmark : public QWidget {
  Q_OBJECT
public:
  explicit Bookmark(QWidget *parent = nullptr);

signals:
};
} // namespace time_line
#endif // BOOKMARK_H
