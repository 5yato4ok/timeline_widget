
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include <QWindow>

namespace time_line {

void MainWindow::setGenerationButtonStatus(bool status) {
  ui.pushButton->setDisabled(status);
  ui.pushButton->setToolTip(status
                                ? "Processing generation of bookmarks"
                                : "Push to start new generation of bookmarks");
}

MainWindow::~MainWindow() {
  // delete dialog
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    gen_handler(this),dialog(this) {
  ui.setupUi(this);
  ui.pushButton->setToolTip("Push to start new generation of bookmarks");
  ui_dialog.setupUi(&dialog);

  ui.graphicsLayout->addWidget(&view_handler);

  QObject::connect(ui.pushButton, &QPushButton::pressed, &dialog,
                   &QDialog::open);
  QObject::connect(ui_dialog.startButton, &QPushButton::clicked, &dialog,
                   &QDialog::close);
  QObject::connect(ui_dialog.cancelButton, &QPushButton::clicked, &dialog,
                   &QDialog::close);

  QObject::connect(ui_dialog.startButton, &QPushButton::clicked, &gen_handler,
                   &GenerationHandler::startGeneration);

  QObject::connect(ui_dialog.spinBox, &QSpinBox::valueChanged, &gen_handler,
                   &GenerationHandler::setNumOfBkmrs);

  QObject::connect(&view_handler, &ViewHandler::recalcVisibleObjectRequired,
                   &gen_handler, &GenerationHandler::generateVisibleObjs);

  QObject::connect(&gen_handler, &GenerationHandler::generationStatusChanged,
                   this, &MainWindow::setGenerationButtonStatus);

  QObject::connect(&gen_handler, &GenerationHandler::visibleObjsGenerated,
                   &view_handler, &ViewHandler::drawVisibleObjects);
}

} // namespace time_line
