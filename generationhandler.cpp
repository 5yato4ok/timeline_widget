
#include "generationhandler.h"
#include <future>
#include <thread>
#include <QThread>

namespace time_line {
using namespace std;
GenerationHandler::GenerationHandler(QWidget *parent)
    : QWidget{parent}, num_of_bkmrs(0) {
}
void GenerationHandler::startGeneration() {
  bkmrk_storage_parted.clear();
  visible_objs.clear();
  if (num_of_bkmrs == 0)
    return;
  generateBkmrks();
}

//is called on each button push
void GenerationHandler::generateBkmrks() {
  //generate threads by num of cores if value bigger than 100;
  //each calls generateBkmrksPos and generateVisibleObjs
  //then merge result
  auto cpuCount = num_of_bkmrs > 100 ? QThread::idealThreadCount() : 1;
  bkmrk_storage_parted.resize(cpuCount);

  vector <future <void >> futures;
  const int max_hour = 23;
  const int part_count = num_of_bkmrs / cpuCount;
  for (size_t i = 0; i < cpuCount; i++) {
    double start_hour = i * max_hour / cpuCount;
    double end_hour = i+1 < cpuCount ? ((i+1) * max_hour / cpuCount): max_hour;
    int count = i+1 < cpuCount ? part_count : num_of_bkmrs - i * part_count;
    futures.push_back([this,&start_hour,&end_hour,&count,&i]{
        generateBkmrksPos(start_hour,end_hour,count,i);
    });
  }
}

vector<DrawObj> GenerationHandler::mergeGeneratedParts(const visible_objs_parted &parts) {
  vector<DrawObj> res;
  return res;
}

void GenerationHandler::generateBkmrksPos (int start_hour, int last_hour,int count, int thread_store_idx){

}

//is called onbutton push and resize
void GenerationHandler::generateVisibleObjs() {
  if (bkmrk_storage_parted.empty())
    return;
  visible_objs_parted objs_parted;
  auto cpuCount = num_of_bkmrs > 100 ? QThread::idealThreadCount() : 1;

  vector <future <void >> futures;
  for (size_t i = 0; i < cpuCount; i++) {
    futures.push_back([this,&i]{
        generateVisibleObjsSingleThread(i);
    });
  }

  for(auto& f: futures) {
    objs_parted.push_back(f.get());
  }

  visible_objs = mergeGeneratedParts(objs_parted);
  emit visibleObjectesGenerated(visible_objs);
}

std::vector<DrawObj> GenerationHandler::generateVisibleObjsSingleThread(int thread_store_idx) {
  return {};
}

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
}
} // namespace time_line
