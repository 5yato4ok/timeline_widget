
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
  void generateVisibleObjs();
signals:
  void visibleObjectesGenerated(std::vector<DrawObj>& objs);

private:
  using bkmrks_ordered_by_start = std::vector<std::pair<double,double>>;
  using visible_objs_parted = std::vector<std::vector<DrawObj>>;

  void generateBkmrks();
  void generateBkmrksPos(int start_hour, int last_hour, int count, int thread_store_idx=0);
  std::vector<DrawObj> generateVisibleObjsSingleThread(int thread_store_idx, int start_bkmrk);
  std::vector<DrawObj> mergeGeneratedParts(const visible_objs_parted &);

  const int MAX_CNT_BOOKMARK = 100000000;
  const double MAX_BKMRK_DURATION = 3;
  const double MIN_BKMRK_DURATION = 0.1;

  size_t num_of_bkmrs;
  int hour_scale_pixels;
  bool bkmrks_generated;
  std::vector<bkmrks_ordered_by_start> bkmrk_storage_parted;
  std::vector<DrawObj> visible_objs;
};
} // namespace time_line
#endif // GENERATIONHANDLER_H
