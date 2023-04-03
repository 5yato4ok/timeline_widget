
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include "time_line.h"
#include <QObject>
#include "timelineitem.h"
#include <utility>
#include <vector>
#include <mutex>

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
  void generateVisibleObjs(const PartedStorageOfBkmrks& bkmrk_storage_parted);
  void moveCache(PartedStorageOfBkmrks& dest);
signals:
  void visibleObjectesGenerated(const std::vector<TimeLineItem>& objs);
  void generationStatusChanged(bool);
  void bkmrksGenerated();

private:
  using VisibleObjsParted = std::vector<std::vector<TimeLineItem>>;

  void generateBkmrks();
  void generateBkmrksPos(int start_sec, int last_sec, int count, int thread_store_idx=0);
  std::vector<TimeLineItem> generateVisibleObjsSingleThread(const BkmrksOrderedByStart& bkmrks, int start_bkmrk);
  std::vector<TimeLineItem> mergeGeneratedParts(const VisibleObjsParted &);
  bool isLaunchedLauncherThread();

  const int MAX_CNT_BOOKMARK = 100000000;
  const int MAX_BKMRK_DURATION = 3*60*60;
  const int MIN_BKMRK_DURATION = 6*60;

  size_t num_of_bkmrs;
  int hour_scale_pixels;
  PartedStorageOfBkmrks bkmrk_storage_parted;
  const int approximate_min_scale = 30;
  std::mutex m;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
