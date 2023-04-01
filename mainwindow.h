
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "generationhandler.h"
#include "time_line.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

namespace time_line {
class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr);
private:
  TimeLine *time_line;
  GenerationHandler* handler;
  Ui::MainWindow ui;
};
} // namespace time_line
#endif // MAINWINDOW_H
