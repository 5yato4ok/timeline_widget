
#include "generationhandler.h"

namespace time_line {
GenerationHandler::GenerationHandler(QObject *parent) : QObject{parent} {}
void GenerationHandler::startGeneration(){};
void GenerationHandler::setNumOfBkmrs(size_t num){
    num_of_bkmrs = num> MAX_CNT_BOOKMARK ? 0 : num;
};
} // namespace time_line
