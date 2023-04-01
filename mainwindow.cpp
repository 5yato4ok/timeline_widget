
#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace time_line {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), time_line(new TimeLine(this)) {
  ui.setupUi(this);
  ui.time_line_layout->addWidget(time_line);
  handler = new GenerationHandler(ui.bkmrs_layout,this);

  QObject::connect(ui.pushButton, &QPushButton::clicked, handler,
                   &GenerationHandler::startGeneration);
  QObject::connect(ui.spinBox, &QSpinBox::valueChanged, handler,
                   &GenerationHandler::setNumOfBkmrs);
}

} // namespace time_line
