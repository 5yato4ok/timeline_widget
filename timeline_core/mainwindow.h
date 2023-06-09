
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "generationhandler.h"
#include "time_line.h"
#include "ui_dialog.h"
#include "ui_mainwindow.h"
#include "viewhandler.h"
#include <QMainWindow>

namespace time_line {
/**
 * @brief user's entry point.
 * sets up the signals slots between GUI generator and Data generator
 */
class MainWindow : public QMainWindow {
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
public slots:
  void setGenerationButtonStatus(bool status);

private:
  GenerationHandler gen_handler;
  ViewHandler view_handler;
  Ui::MainWindow ui;
  Ui::Dialog ui_dialog;
  QDialog dialog;
};
} // namespace time_line
#endif // MAINWINDOW_H
