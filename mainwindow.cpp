
#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace time_line {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  ui.setupUi(this);

  view_handler = new ViewHandler(this);
  ui.graphicsLayout->addWidget(view_handler);
  gen_handler = new GenerationHandler(nullptr,this);

}

} // namespace time_line
