
#ifndef GENERATIONHANDLER_H
#define GENERATIONHANDLER_H

#include "bookmark.h"
#include "groupbookmark.h"
#include "time_line.h"
#include <QObject>
#include "drawobj.h"
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
  void visibleObjectesGenerated(const std::vector<DrawObj>& objs);
  void generationStatusChanged(bool);
  void bkmrksGenerated();

private:
  using VisibleObjsParted = std::vector<std::vector<DrawObj>>;

  void generateBkmrks();
  void generateBkmrksPos(double start_hour, double last_hour, int count, int thread_store_idx=0);
  std::vector<DrawObj> generateVisibleObjsSingleThread(const BkmrksOrderedByStart& bkmrks, int start_bkmrk);
  std::vector<DrawObj> mergeGeneratedParts(const VisibleObjsParted &);
  bool isLaunchedLauncherThread();

  const int MAX_CNT_BOOKMARK = 100000000;
  const double MAX_BKMRK_DURATION = 3;
  const double MIN_BKMRK_DURATION = 0.1;

  size_t num_of_bkmrs;
  int hour_scale_pixels;
  PartedStorageOfBkmrks bkmrk_storage_parted;
  const int approximate_min_scale = 30;
  std::mutex m;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
