
#include "generationhandler.h"

namespace time_line {
GenerationHandler::GenerationHandler(QLayout *layout, QObject *parent)
    : QObject{parent}, num_of_bkmrs(0),bkmrks_layout(layout) {}
void GenerationHandler::startGeneration() {
    clearLayout();
    bkmrk_storage_parted.clear();
    group_bkmrk_storage.clear();
    if (num_of_bkmrs == 0) return;
    generateBkmrks();
    generateGroups();
};

void GenerationHandler::clearLayout() {
    foreach (QObject *object, bkmrks_layout->children()) {
        QWidget *widget = qobject_cast<QWidget*>(object);
        if (widget) {
            bkmrks_layout->removeWidget(widget);
        }
    }
}

void GenerationHandler::generateBkmrks(){};
void GenerationHandler::generateGroups(){};

void GenerationHandler::setNumOfBkmrs(size_t num) {
  num_of_bkmrs = num > MAX_CNT_BOOKMARK ? 0 : num;
};
} // namespace time_line
