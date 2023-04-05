
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include "time_line.h"
#include "timelineitem.h"
#include <QObject>
#include <mutex>
#include <utility>
#include <vector>

namespace time_line {
/**
 * @brief: controls data generation.
 * generates bookmarks intervals in separate threads,
 * each thread works on same storage, but on different position in storage,
 * which allows not to use mutexes. calculates visible object after grouping.
 * parallel generation of multiple sets of bookmarks is not supported.
 * parrallel recalculation of visible object during generation is supported.
 */
class GenerationHandler : public QWidget {
  Q_OBJECT
public:
  explicit GenerationHandler(QWidget *parent = nullptr);

  using BkmrksOrderedByStart = std::vector<std::pair<int, int>>;
  using PartedStorageOfBkmrks = std::vector<BkmrksOrderedByStart>;
public slots:
  void startGeneration();
  void setNumOfBkmrs(size_t num);
  void generateVisibleObjs();
signals:
  void visibleObjsGenerated(const VisibleObjs &);
  void generationStatusChanged(bool);

private:
  void generateBkmrks();
  void generateBkmrksSingleThread(int start_millisec, int last_millisec, int count,
                                  BkmrksOrderedByStart &dst);
  VisibleObjs
  generateVisibleObjsSingleThread(const BkmrksOrderedByStart &bkmrks,
                                  int start_bkmrk, double scale);
  VisibleObjs mergeVisibleObjsParts(const VisibleObjsParted &objs_to_merge, double scale);
  bool isProcessingGeneration();

  const int MAX_CNT_BOOKMARK = 100000000;
  const int MAX_BKMRK_DURATION = 3 * 60 * 60 * 60;
  const int MIN_BKMRK_DURATION = 1 * 60;

  size_t num_of_bkmrs;
  PartedStorageOfBkmrks bkmrk_storage_parted;
  const double approximate_min_scale = 30/60/60/60;
  std::mutex gen_mutex;
  std::mutex store_mutex;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
