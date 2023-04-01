
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include <QObject>
#include <QLayout>
#include <set>
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
  explicit GenerationHandler(QLayout *layout, QObject *parent = nullptr);
public slots:
  void startGeneration();
  void setNumOfBkmrs(size_t num);

private:
  void clearLayout();
  void generateBkmrks();
  void generateGroups();

  static bool compareBkmrksPtr(const std::shared_ptr<Bookmark> &a,
                               const std::shared_ptr<Bookmark> &b) {
    return a->getStart() < b->getStart();
  }
  const int MAX_CNT_BOOKMARK = 100000000;
  using bkmrks_ordered_by_start =
      std::multiset<std::shared_ptr<Bookmark>, decltype(compareBkmrksPtr) *>;
  size_t num_of_bkmrs;
  QLayout* bkmrks_layout;
  std::vector<bkmrks_ordered_by_start> bkmrk_storage_parted;
  std::unordered_set<std::shared_ptr<GroupBookMark>> group_bkmrk_storage;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
