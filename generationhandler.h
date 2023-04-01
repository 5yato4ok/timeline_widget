
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include <QObject>
#include <map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace time_line {
/**
 * @brief: generate buttons and groups, recalculate them on width resize
 * keeps storage of groups, bookmarks
 */
class GenerationHandler : public QObject {
  Q_OBJECT
public:
  explicit GenerationHandler(QObject *parent = nullptr);
public slots:
  void startGeneration();
  void setNumOfBkmrs(size_t num);

private:
  const int MAX_CNT_BOOKMARK = 100000000;
  using bkmrks_ordered_by_start =
      std::map<int, std::vector<std::shared_ptr<Bookmark>>>;
  size_t num_of_bkmrs;
  std::vector<bkmrks_ordered_by_start> bkmrk_storage_parted;
  std::unordered_set<std::shared_ptr<GroupBookMark>> group_bkmrk_storage;
  std::vector<QWidget *> visible_objs;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
