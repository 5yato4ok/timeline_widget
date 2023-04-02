
#include "generationhandler.h"
#include <future>
#include <thread>
#include <QThread>
#include <random>
#include <algorithm>
#include "profile.h"

namespace time_line {
using namespace std;
GenerationHandler::GenerationHandler(QWidget *parent)
    : QWidget{parent}, num_of_bkmrs(0), hour_scale_pixels(0), bkmrks_generated(false) {
}
void GenerationHandler::startGeneration() {
  bkmrks_generated = false;
  bkmrk_storage_parted.clear();
  visible_objs.clear();
  hour_scale_pixels = parentWidget() ? parentWidget()->width() / 23: approximate_min_scale;
  if (num_of_bkmrs == 0)
    return;
  LOG_DURATION("generation_bookmark_total") {
  generateBkmrks();
  }
  bkmrks_generated = true;
  LOG_DURATION("generation_visible_objs") {
  generateVisibleObjs();
  }
}

//is called on each button push
void GenerationHandler::generateBkmrks() {
  //generate threads by num of cores if value bigger than 100;
  //each calls generateBkmrksPos and generateVisibleObjs
  //then merge result
  auto cpuCount = num_of_bkmrs > 100 ? QThread::idealThreadCount() : 1;
  bkmrk_storage_parted.resize(cpuCount);
  vector <future <void>> futures;
  const int max_hour = 23;
  const int part_count = num_of_bkmrs / cpuCount;
  for (size_t i = 0; i < cpuCount; i++) {
    double start_hour = i * max_hour / cpuCount;
    double end_hour = i+1 < cpuCount ? ((i+1) * max_hour / cpuCount): max_hour;
    int count = i+1 < cpuCount ? part_count : num_of_bkmrs - i * part_count;
    bkmrk_storage_parted[i].reserve(count);
    futures.push_back(async(std::launch::async,[this,start_hour,end_hour,count,i]{
        generateBkmrksPos(start_hour,end_hour,count,i);
    }));
  }
}

vector<DrawObj> GenerationHandler::mergeGeneratedParts(const visible_objs_parted &parts) {
  if (parts.size()==1) return parts.front();
  vector<DrawObj> res = parts.front();
  for(int i = 1; i < parts.size();i++) {
    auto& curMergePart = parts.at(i);
    auto it_beg =  curMergePart.begin();
    if (res.back().intersects(curMergePart.front(), hour_scale_pixels)) {
        res.back().bkmrks_idxs.insert(res.back().bkmrks_idxs.end(),curMergePart.front().bkmrks_idxs.begin(),curMergePart.front().bkmrks_idxs.end());
        res.back().end_hour = curMergePart.front().end_hour;
        it_beg = next(it_beg);
    }
    res.insert(res.end(), it_beg,curMergePart.end());
  }
  return res;
}

void GenerationHandler::generateBkmrksPos (double start_hour, double last_hour,int count, int thread_store_idx){
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> start_distr(start_hour, last_hour);
  uniform_real_distribution<> diff_distr(0, MAX_BKMRK_DURATION);
  auto& cur_thread_store = bkmrk_storage_parted.at(thread_store_idx);
  LOG_DURATION("generation of nums") {
  for(int n=0; n<count; ++n) {
    auto start = start_distr(gen);
    cur_thread_store.push_back({start, start+diff_distr(gen)});
  }
  }
  LOG_DURATION("sorting of nums") {
  sort(cur_thread_store.begin(), cur_thread_store.end());
  }
}

//is called onbutton push and resize
void GenerationHandler::generateVisibleObjs() {
  if (bkmrk_storage_parted.empty()|| !bkmrks_generated)
    return;
  visible_objs_parted objs_parted;
  auto cpuCount = num_of_bkmrs > 100 ? QThread::idealThreadCount() : 1;
  vector <future <vector<DrawObj>>> futures;
  for (size_t i = 0; i < cpuCount; i++) {
    futures.push_back(async(std::launch::async,[this,i]{
        int start_bkmrk = i > 0 ? bkmrk_storage_parted[i-1].size() : 1;
        return generateVisibleObjsSingleThread(i,start_bkmrk);
    }));
  }

  for(auto& f: futures) {
    objs_parted.push_back(f.get());
  }

  visible_objs = mergeGeneratedParts(objs_parted);
  if (!visible_objs.empty()){
    emit visibleObjectesGenerated(visible_objs);
  }
}


vector<DrawObj> GenerationHandler::generateVisibleObjsSingleThread(int thread_store_idx, int start_bkmrk) {
  auto& cur_thread_store = bkmrk_storage_parted.at(thread_store_idx);
  if (cur_thread_store.empty()) return {};
  DrawObj cur_group( cur_thread_store.front().first, cur_thread_store.front().second,{1});
  vector<DrawObj> res;
  for(int i = 1; i < cur_thread_store.size();i++) {
    if(cur_group.intersects(cur_thread_store.at(i), hour_scale_pixels)) {
        cur_group.bkmrks_idxs.push_back(start_bkmrk + i + 1);
        cur_group.end_hour = cur_thread_store.at(i).second;
    } else {
        res.push_back(cur_group);
        cur_group = DrawObj(cur_thread_store.at(i).first,cur_thread_store.at(i).second, {i});
    }
  }
  res.push_back(cur_group);
  return res;
}

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
}
} // namespace time_line
