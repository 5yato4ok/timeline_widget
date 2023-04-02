
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include "time_line.h"
#include <QObject>
#include "drawobj.h"
#include <utility>
#include <vector>

namespace time_line {
/**
 * @brief: generate bookmarks intervals,calculate visible object after grouping
 */
class GenerationHandler : public  QWidget {
  Q_OBJECT
public:
  explicit GenerationHandler(QWidget *parent = nullptr);
public slots:
  void startGeneration();
  void setNumOfBkmrs(size_t num);
signals:
  void visibleObjectesGenerated(std::vector<DrawObj>& objs);

private:
  using bkmrks_ordered_by_start = std::vector<std::pair<size_t,size_t>>;
  using visible_objs_parted = std::vector<std::vector<DrawObj>>;

  void generateBkmrks();
  bkmrks_ordered_by_start generateBkmrksPos(int start_hour) const;
  std::vector<DrawObj> generateVisibleObjs(const bkmrks_ordered_by_start&);
  void mergeGeneratedParts(const visible_objs_parted &);

  const int MAX_CNT_BOOKMARK = 100000000;
  const static double MAX_BKMRK_DURATION = 3;

  size_t num_of_bkmrs;
  std::vector<bkmrks_ordered_by_start> bkmrk_storage_parted;
  std::vector<DrawObj> visible_objs;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
