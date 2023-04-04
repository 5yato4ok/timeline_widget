
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
 * each thread works on same storage, but on different position in storage, which allows not to use mutexes.
 * calculates visible object after grouping.
 * parallel generation of multiple sets of bookmarks is not supported.
 * parrallel recalculation of visible object during generation is supported.
 */
class GenerationHandler : public QWidget {
  Q_OBJECT
public:
  explicit GenerationHandler(QWidget *parent = nullptr);
public slots:
  void startGeneration();
  void setNumOfBkmrs(size_t num);
  void generateVisibleObjs(const PartedStorageOfBkmrks &bkmrk_storage_parted);
  void moveCache(PartedStorageOfBkmrks &dest);
signals:
  void visibleObjectesGenerated(const std::vector<TimeLineItem> &objs);
  void generationStatusChanged(bool);
  void bkmrksGenerated();

private:
  using VisibleObjsParted = std::vector<std::vector<TimeLineItem>>;

  void generateBkmrks();
  void generateBkmrksPos(int start_sec, int last_sec, int count,
                         int thread_store_idx = 0);
  std::vector<TimeLineItem>
  generateVisibleObjsSingleThread(const BkmrksOrderedByStart &bkmrks,
                                  int start_bkmrk, double hour_scale);
  std::vector<TimeLineItem> mergeGeneratedParts(const VisibleObjsParted & objs_to_merge,
                                                double hour_scale_pixels);
  bool isLaunchedLauncherThread();

  const int MAX_CNT_BOOKMARK = 100000000;
  const int MAX_BKMRK_DURATION = 3 * 60 * 60;
  const int MIN_BKMRK_DURATION = 6 * 60;

  size_t num_of_bkmrs;
  PartedStorageOfBkmrks bkmrk_storage_parted;
  const int approximate_min_scale = 30;
  std::mutex m;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
