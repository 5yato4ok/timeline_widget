
#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace time_line {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  ui.setupUi(this);

  view_handler = new ViewHandler(this);
  ui.graphicsLayout->addWidget(view_handler);
  gen_handler = new GenerationHandler(nullptr,this);

  QObject::connect(ui.pushButton, &QPushButton::clicked, gen_handler,
                   &GenerationHandler::startGeneration);
  QObject::connect(ui.spinBox, &QSpinBox::valueChanged, gen_handler,
                   &GenerationHandler::setNumOfBkmrs);
}

} // namespace time_line
