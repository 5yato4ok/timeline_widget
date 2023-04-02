
#ifndef DATADESC_H
#define DATADESC_H
#include <vector>
#include "timeline.h"
namespace time_line {
class DrawObj{
public:
    DrawObj() = default;
    bool isGroupObj() const {
        return bkmrks_idxs.size() == 1;
    }

    bool intersects(const DrawObj& b, size_t hour_scale_pixels) {
        return abs(b.start_hour - start_hour) * hour_scale_pixels <= MAX_PIXEL_DIFF;
    }

    double start_hour;
    double end_hour;
    std::vector<int> bkmrks_idxs;
    const int MAX_PIXEL_DIFF = 100;
};
}
#endif // DATADESC_H
