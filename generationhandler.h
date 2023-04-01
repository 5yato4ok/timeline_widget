
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include <QObject>

namespace time_line {
/**
 * @brief: generate buttons and groups, recalculate them on width resize
 * keeps storage of groups, bookmarks
 */
class GenerationHandler : public QObject {
  Q_OBJECT
public:
  explicit GenerationHandler(QObject *parent = nullptr);

signals:
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
