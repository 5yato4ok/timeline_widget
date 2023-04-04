
#include "generationhandler.h"
#include "profile.h"
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
    } catch(...) {
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
  auto cpuCount = num_of_bkmrs > 100 ? QThread::idealThreadCount() : 1;
  PartedStorageOfBkmrks bkmrks_parted;
  bkmrks_parted.resize(cpuCount);
  std::vector<std::future<void>> futures;
  const int max_sec = 23 * 60 * 60;
  const int part_count = num_of_bkmrs / cpuCount;
  for (size_t i = 0; i < cpuCount; i++) {
    int start_sec = i * max_sec / cpuCount;
    int end_sec = i + 1 < cpuCount ? ((i + 1) * max_sec / cpuCount) : max_sec;
    int count = i + 1 < cpuCount ? part_count : num_of_bkmrs - i * part_count;
    bkmrks_parted[i].reserve(count);
    futures.push_back(async(std::launch::async, [this, start_sec, end_sec,
                                                 count, i, &bkmrks_parted] {
      generateBkmrksSingleThread(start_sec, end_sec, count, bkmrks_parted[i]);
    }));
  }

  for (auto &f : futures) {
    f.get();
  }
  store_mutex.lock();
  bkmrk_storage_parted = std::move(bkmrks_parted);
  store_mutex.unlock();
}

VisibleObjs
GenerationHandler::mergeVisibleObjsParts(const VisibleObjsParted &parts,
                                         double hour_scale_pixels) {
  if (parts.size() == 1)
    return parts.front();
  vector<TimeLineItem> res = parts.front();
  for (int i = 1; i < parts.size(); i++) {
    auto &curMergePart = parts.at(i);
    auto it_beg = curMergePart.begin();
    if (res.back().intersects(curMergePart.front(), hour_scale_pixels)) {
      res.back().bkmrks_idxs.insert(res.back().bkmrks_idxs.end(),
                                    curMergePart.front().bkmrks_idxs.begin(),
                                    curMergePart.front().bkmrks_idxs.end());
      res.back().end_sec = curMergePart.front().end_sec;
      it_beg = next(it_beg);
    }
    res.insert(res.end(), it_beg, curMergePart.end());
  }
  return res;
}

void GenerationHandler::generateBkmrksSingleThread(
    int start_sec, int last_sec, int count,
    BkmrksOrderedByStart &cur_thread_store) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> start_distr(start_sec, last_sec);
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
    double hour_scale_pixels =
        parentWidget() ? parentWidget()->width() / 23 : approximate_min_scale;
    for (size_t i = 0; i < cpuCount; i++) {
      if (i > 0) {
        start_bkmrk += bkmrk_storage_parted.at(i - 1).size();
      }
      futures.push_back(
          async(std::launch::async, [this, i, start_bkmrk, hour_scale_pixels] {
            return generateVisibleObjsSingleThread(
                bkmrk_storage_parted.at(i), start_bkmrk, hour_scale_pixels);
          }));
    }

    for (auto &f : futures) {
      objs_parted.push_back(f.get());
    }

    emit visibleObjsGenerated(
        mergeVisibleObjsParts(objs_parted, hour_scale_pixels));
  });
  launcher.detach();
}

vector<TimeLineItem> GenerationHandler::generateVisibleObjsSingleThread(
    const BkmrksOrderedByStart &bkmrks, int start_bkmrk,
    double hour_scale_pixels) {
  if (bkmrks.empty())
    return {};
  TimeLineItem cur_group(bkmrks.front(), {start_bkmrk + 1});
  VisibleObjs res;
  for (int i = 1; i < bkmrks.size(); i++) {
    int bkmrk_idx = start_bkmrk + i + 1;
    if (cur_group.intersects(bkmrks.at(i), hour_scale_pixels)) {
      cur_group.bkmrks_idxs.push_back(bkmrk_idx);
      cur_group.end_sec = bkmrks.at(i).second;
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
