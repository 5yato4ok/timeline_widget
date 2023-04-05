
#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H
#include <cmath>
#include <vector>

namespace time_line {
/**
 * @brief describes one item on timeline
 */
class TimeLineItem {
public:
  TimeLineItem() = default;
  TimeLineItem(int start, int end, const std::vector<int> &idxs, int p_y = 0,
               double scale = 0)
      : start_millisec(start), end_millisec(end), bkmrks_idxs(idxs), y(p_y),
      sec_scale(scale) {}
  TimeLineItem(const std::pair<int, int> &range, const std::vector<int> &idxs)
      : TimeLineItem(range.first, range.second, idxs) {}
  bool isGroupObj() const { return bkmrks_idxs.size() > 1; }

  bool intersects(const std::pair<int, int> &b, int sec_per_pixel) const {
      return std::abs(b.first - start_millisec)  <= (MAX_PIXEL_DIFF * sec_per_pixel);
  }

  bool intersects(const TimeLineItem &b, int sec_per_pixel) const {
      return intersects({b.start_millisec, b.end_millisec}, sec_per_pixel);
  }

  int start_millisec;
  int end_millisec;
  std::vector<int> bkmrks_idxs;
  int y;
  double sec_scale;
  int MAX_PIXEL_DIFF = 100;
};

using VisibleObjs = std::vector<TimeLineItem>;
using VisibleObjsParted = std::vector<VisibleObjs>;

} // namespace time_line
#endif // TIMELINEITEM_H
