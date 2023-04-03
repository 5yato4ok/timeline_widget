
#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace time_line {

void MainWindow::setGenerationButtonStatus(bool status) {
    ui.pushButton->setDisabled(status);
    ui.pushButton->setToolTip(status ? "Processing generation of bookmarks":
                                  "Push to start new generation of bookmarks");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  ui.setupUi(this);
  ui.pushButton->setToolTip("Push to start new generation of bookmarks");

  view_handler = new ViewHandler(this);
  ui.graphicsLayout->addWidget(view_handler);
  gen_handler = new GenerationHandler(this);

  QObject::connect(ui.pushButton, &QPushButton::clicked, gen_handler,
                   &GenerationHandler::startGeneration);
  QObject::connect(ui.spinBox, &QSpinBox::valueChanged, gen_handler,
                   &GenerationHandler::setNumOfBkmrs);

  QObject::connect(gen_handler, &GenerationHandler::bkmrksGenerated, view_handler,
                   &ViewHandler::cacheBkmrks);

  QObject::connect(view_handler, &ViewHandler::recalcVisibleObjectRequired, gen_handler,
                   &GenerationHandler::generateVisibleObjs);
  QObject::connect(gen_handler, &GenerationHandler::generationStatusChanged, this,
                   &MainWindow::setGenerationButtonStatus);

  QObject::connect(gen_handler, &GenerationHandler::visibleObjectesGenerated, view_handler,
                   &ViewHandler::drawVisibleObjects);

}

} // namespace time_line
