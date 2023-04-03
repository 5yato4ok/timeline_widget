
#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace time_line {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  ui.setupUi(this);

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
//  QObject::connect(view_handler, &ViewHandler::generationStatusRequied, gen_handler,
//                   &GenerationHandler::checkGenerationStatus);

  QObject::connect(gen_handler, &GenerationHandler::visibleObjectesGenerated, view_handler,
                   &ViewHandler::drawVisibleObjects);

}

} // namespace time_line
