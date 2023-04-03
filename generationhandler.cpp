
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
    : QWidget{parent}, num_of_bkmrs(0), hour_scale_pixels(0) {
}


bool GenerationHandler::isLaunchedLauncherThread() {
    if (m.try_lock()) {
        m.unlock();
        return false;
    }
    return true;
}

void GenerationHandler::startGeneration() {
    if(isLaunchedLauncherThread()) {
        return; //for now ignore generation of two different sets of bkmrks in parallel
    }

    std::thread launcher([&]{
        lock_guard<mutex> lock(m);
        emit generationStatusChanged(true);
        bkmrk_storage_parted.clear();
        hour_scale_pixels = parentWidget() ? parentWidget()->width() / 23: approximate_min_scale;
        if (num_of_bkmrs == 0)
            return;
        generateBkmrks();
        emit bkmrksGenerated(bkmrk_storage_parted);
        bkmrk_storage_parted.clear();
        emit generationStatusChanged(false);
    });

    launcher.detach();

}

//is called on each button push
void GenerationHandler::generateBkmrks() {
  //generate threads by num of cores if value bigger than 100;
  //each calls generateBkmrksPos
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

vector<DrawObj> GenerationHandler::mergeGeneratedParts(const VisibleObjsParted &parts) {
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
  //LOG_DURATION("generation of nums") {
  for(int n=0; n<count; ++n) {
    auto start = start_distr(gen);
    cur_thread_store.push_back({start, start+diff_distr(gen)});
  }
  //}
  //LOG_DURATION("sorting of nums") {
  sort(cur_thread_store.begin(), cur_thread_store.end());
  //}
}

//is called onbutton push and resize
void GenerationHandler::generateVisibleObjs(const PartedStorageOfBkmrks& bkmrk_storage_parted) {
  if (bkmrk_storage_parted.empty()){
    emit visibleObjectesGenerated({});
  }
  VisibleObjsParted objs_parted;
  auto cpuCount = bkmrk_storage_parted.size();
  vector <future <vector<DrawObj>>> futures;
  for (size_t i = 0; i < cpuCount; i++) {
    futures.push_back(async(std::launch::async,[this,i,&bkmrk_storage_parted]{
        int start_bkmrk = i > 0 ? bkmrk_storage_parted.at(i-1).size() : 1;
        return generateVisibleObjsSingleThread(bkmrk_storage_parted.at(i), start_bkmrk);
    }));
  }

  for(auto& f: futures) {
    objs_parted.push_back(f.get());
  }

  emit visibleObjectesGenerated(mergeGeneratedParts(objs_parted));
}


vector<DrawObj> GenerationHandler::generateVisibleObjsSingleThread(const BkmrksOrderedByStart& bkmrks, int start_bkmrk) {
  if (bkmrks.empty()) return {};
  DrawObj cur_group( bkmrks.front().first, bkmrks.front().second,{1});
  vector<DrawObj> res;
  for(int i = 1; i < bkmrks.size();i++) {
    if(cur_group.intersects(bkmrks.at(i), hour_scale_pixels)) {
        cur_group.bkmrks_idxs.push_back(start_bkmrk + i + 1);
        cur_group.end_hour = bkmrks.at(i).second;
    } else {
        res.push_back(cur_group);
        cur_group = DrawObj(bkmrks.at(i).first,bkmrks.at(i).second, {i});
    }
  }
  res.push_back(cur_group);
  return res;
}

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
}
} // namespace time_line
