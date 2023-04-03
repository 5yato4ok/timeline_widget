
#ifndef DATADESC_H
#define DATADESC_H
#include <vector>


namespace time_line {
using BkmrksOrderedByStart = std::vector<std::pair<double,double>>;
using PartedStorageOfBkmrks = std::vector<BkmrksOrderedByStart>;

class DrawObj{
public:
    DrawObj() = default;
    DrawObj(double start, double end, const std::vector<int> &idxs) :
        start_hour(start),end_hour(end),bkmrks_idxs(idxs){}
    bool isGroupObj() const {
        return bkmrks_idxs.size() > 1;
    }

    bool intersects(const std::pair<double,double>& b, size_t hour_scale_pixels) const {
        return abs(b.first - start_hour) * hour_scale_pixels <= MAX_PIXEL_DIFF;
    }

    bool intersects(const DrawObj& b, size_t hour_scale_pixels) const {
        return intersects({b.start_hour,b.end_hour},hour_scale_pixels);
    }

    double start_hour;
    double end_hour;
    std::vector<int> bkmrks_idxs;
    int MAX_PIXEL_DIFF = 100;
};

struct DrawWidgetDesc {
    double start_hour;
    double end_hour;
    std::vector<int> idxs;
    int y;
    double scale;
};

}
#endif // DATADESC_H
