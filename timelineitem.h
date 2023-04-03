
#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H
#include <vector>
#include <cmath>

namespace time_line {
using BkmrksOrderedByStart = std::vector<std::pair<int, int>>;
using PartedStorageOfBkmrks = std::vector<BkmrksOrderedByStart>;

/**
 * @brief describes one item on timeline
 */
class TimeLineItem {
public:
  TimeLineItem() = default;
  TimeLineItem(int start, int end, const std::vector<int> &idxs, int p_y = 0,
               double scale = 0)
      : start_sec(start), end_sec(end), bkmrks_idxs(idxs), y(p_y),
        hour_scale(scale) {}
  TimeLineItem(const std::pair<int, int> &range, const std::vector<int> &idxs)
      : TimeLineItem(range.first, range.second, idxs) {}
  bool isGroupObj() const { return bkmrks_idxs.size() > 1; }

  bool intersects(const std::pair<int, int> &b, int hour_scale_pixels) const {
    double diff_in_hour = (std::abs(b.first - start_sec) / (60 * 60));
    return diff_in_hour * hour_scale_pixels <= MAX_PIXEL_DIFF;
  }

  bool intersects(const TimeLineItem &b, int hour_scale_pixels) const {
    return intersects({b.start_sec, b.end_sec}, hour_scale_pixels);
  }

  int start_sec;
  int end_sec;
  std::vector<int> bkmrks_idxs;
  int y;
  double hour_scale;
  int MAX_PIXEL_DIFF = 100;
};

} // namespace time_line
#endif // TIMELINEITEM_H
