
#include "generationhandler.h"

namespace time_line {
GenerationHandler::GenerationHandler(QWidget *parent)
    : QWidget{parent}, num_of_bkmrs(0) {
}
void GenerationHandler::startGeneration() {
  bkmrk_storage_parted.clear();
  visible_objs.clear();
  if (num_of_bkmrs == 0)
    return;
  generateBkmrks();
};

void GenerationHandler::generateBkmrks() {
  //generate threads by num of cores;
  //each calls generateBkmrksPos and generateVisibleObjs
  //then merge result
  emit visibleObjectesGenerated(visible_objs);
}

void GenerationHandler::mergeGeneratedParts(const visible_objs_parted &parts) {
//save to visible_objs
}

GenerationHandler::bkmrks_ordered_by_start GenerationHandler::generateBkmrksPos (int start_hour){
  return {};
}

std::vector<DrawObj> GenerationHandler::generateVisibleObjs(const bkmrks_ordered_by_start& part) {

}

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
}
} // namespace time_line
