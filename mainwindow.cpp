
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWindow>
#include <QDialog>

namespace time_line {

void MainWindow::setGenerationButtonStatus(bool status) {
    ui.pushButton->setDisabled(status);
    ui.pushButton->setToolTip(status ? "Processing generation of bookmarks":
                                  "Push to start new generation of bookmarks");
}

MainWindow::~MainWindow(){
    //delete dialog
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
  ui.setupUi(this);
  ui.pushButton->setToolTip("Push to start new generation of bookmarks");
  dialog = new QDialog(this);
  ui_dialog.setupUi(dialog);

  view_handler = new ViewHandler(this);
  ui.graphicsLayout->addWidget(view_handler);
  gen_handler = new GenerationHandler(this);

  QObject::connect(ui.pushButton, &QPushButton::pressed, dialog, &QDialog::open);
  QObject::connect(ui_dialog.startButton, &QPushButton::clicked, dialog, &QDialog::close);
  QObject::connect(ui_dialog.cancelButton, &QPushButton::clicked, dialog, &QDialog::close);

  QObject::connect(ui_dialog.startButton, &QPushButton::clicked, gen_handler,
                   &GenerationHandler::startGeneration);

  QObject::connect(ui_dialog.spinBox, &QSpinBox::valueChanged, gen_handler,
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
