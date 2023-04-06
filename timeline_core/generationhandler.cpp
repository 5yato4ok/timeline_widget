
#include "generationhandler.h"
#include "profile.h"
#include "time_line.h"
#include <QThread>
#include <algorithm>
#include <future>
#include <random>
#include <thread>

namespace time_line {
GenerationHandler::GenerationHandler(QWidget *parent)
    : QWidget{parent}, num_of_bkmrs(0) {}

bool GenerationHandler::isProcessingGeneration() {
  if (gen_mutex.try_lock()) {
    gen_mutex.unlock();
    return false;
  }
  return true;
}

void GenerationHandler::startGeneration() {
  if (isProcessingGeneration()) {
    return; // for now ignore generation of two different sets of bkmrks in
            // parallel
  }

  std::thread launcher([&] {
    std::lock_guard<std::mutex> lock(gen_mutex);
    if (num_of_bkmrs == 0)
      return;
    emit generationStatusChanged(true);
    try {
      generateBkmrks();
    } catch (...) {
      std::lock_guard<mutex> lock(store_mutex);
      bkmrk_storage_parted.clear();
      emit generationStatusChanged(false);
      throw;
    }
    emit generationStatusChanged(false);
    generateVisibleObjs();
  });

  launcher.detach();
}

void GenerationHandler::generateBkmrks() {
  size_t cpuCount = num_of_bkmrs > 100 ? QThread::idealThreadCount() : 1;
  PartedStorageOfBkmrks bkmrks_parted;
  bkmrks_parted.resize(cpuCount);
  std::vector<std::future<void>> futures;
  const int max = 23 * 60 * 60 * 60;
  const int part_count = num_of_bkmrs / cpuCount;
  for (size_t i = 0; i < cpuCount; i++) {
    int start = i * max / cpuCount;
    int end = i + 1 < cpuCount ? ((i + 1) * max / cpuCount) : max;
    size_t count = i + 1 < cpuCount ? part_count : num_of_bkmrs - i * part_count;
    bkmrks_parted[i].reserve(count);
    futures.push_back(
        async(std::launch::async, [this, start, end, count, i, &bkmrks_parted] {
          generateBkmrksSingleThread(start, end, count, bkmrks_parted[i]);
        }));
  }

  for (auto &f : futures) {
    f.get();
  }

  {
    std::lock_guard<mutex> lock(store_mutex);
    bkmrk_storage_parted = std::move(bkmrks_parted);
  }
}

VisibleObjs
GenerationHandler::mergeVisibleObjsParts(const VisibleObjsParted &parts,
                                         double scale) {
  if (parts.size() == 1)
    return parts.front();
  vector<TimeLineItem> res = parts.front();
  for (size_t i = 1; i < parts.size(); i++) {
    auto &curMergePart = parts.at(i);
    auto it_beg = curMergePart.begin();
    if (res.back().intersects(curMergePart.front(), scale)) {
      res.back().bkmrks_idxs.insert(res.back().bkmrks_idxs.end(),
                                    curMergePart.front().bkmrks_idxs.begin(),
                                    curMergePart.front().bkmrks_idxs.end());
      res.back().end_millisec = curMergePart.front().end_millisec;
      it_beg = next(it_beg);
    }
    res.insert(res.end(), it_beg, curMergePart.end());
  }
  return res;
}

void GenerationHandler::generateBkmrksSingleThread(
    int start_millisec, int last_millisec, int count,
    BkmrksOrderedByStart &cur_thread_store) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> start_distr(start_millisec, last_millisec);
  std::uniform_int_distribution<> diff_distr(0, MAX_BKMRK_DURATION);
  for (int n = 0; n < count; ++n) {
    auto start = start_distr(gen);
    cur_thread_store.push_back({start, start + diff_distr(gen)});
  }
  sort(cur_thread_store.begin(), cur_thread_store.end());
}

// is called onbutton push and resize
void GenerationHandler::generateVisibleObjs() {
  std::thread launcher([&] {
    std::lock_guard<mutex> lock(store_mutex);
    if (bkmrk_storage_parted.empty()) {
      emit visibleObjsGenerated({});
      return;
    }
    VisibleObjsParted objs_parted;
    auto cpuCount = bkmrk_storage_parted.size();
    std::vector<std::future<VisibleObjs>> futures;
    int start_bkmrk = 0;
    double millisec_per_pixels =
        parentWidget() ? TimeLine::getMilliSecPerPixel(
                             TimeLine::getMilliSecScale(parentWidget()->rect()))
                       : approximate_min_scale;
    for (size_t i = 0; i < cpuCount; i++) {
      if (i > 0) {
        start_bkmrk += bkmrk_storage_parted.at(i - 1).size();
      }
      futures.push_back(async(
          std::launch::async, [this, i, start_bkmrk, millisec_per_pixels] {
            return generateVisibleObjsSingleThread(
                bkmrk_storage_parted.at(i), start_bkmrk, millisec_per_pixels);
          }));
    }

    for (auto &f : futures) {
      objs_parted.push_back(f.get());
    }

    emit visibleObjsGenerated(
        mergeVisibleObjsParts(objs_parted, millisec_per_pixels));
  });
  launcher.detach();
}

vector<TimeLineItem> GenerationHandler::generateVisibleObjsSingleThread(
    const BkmrksOrderedByStart &bkmrks, int start_bkmrk,
    double millisec_per_pixel) {
  if (bkmrks.empty())
    return {};
  TimeLineItem cur_group(bkmrks.front(), {start_bkmrk + 1});
  VisibleObjs res;
  for (size_t i = 1; i < bkmrks.size(); i++) {
    int bkmrk_idx = start_bkmrk + i + 1;
    if (cur_group.intersects(bkmrks.at(i), millisec_per_pixel)) {
      cur_group.bkmrks_idxs.push_back(bkmrk_idx);
      cur_group.end_millisec = bkmrks.at(i).second;
    } else {
      res.push_back(cur_group);
      cur_group =
          TimeLineItem(bkmrks.at(i).first, bkmrks.at(i).second, {bkmrk_idx});
    }
  }
  res.push_back(cur_group);
  return res;
}

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
}
} // namespace time_line
