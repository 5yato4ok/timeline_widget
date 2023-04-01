
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include <QGraphicsView>
#include "bookmark.h"
#include "groupbookmark.h"
#include "time_line.h"
#include "ui_mainwindow.h"

namespace time_line {
class MainWindow : public QMainWindow {
public:
  MainWindow(QWidget *parent = nullptr)
      : QMainWindow(parent), time_line(new TimeLine(this)) {
    ui.setupUi(this);
    ui.time_line_layout->addWidget(time_line);
  }

private:
  TimeLine *time_line;
  Ui::MainWindow ui;
};
} // namespace time_line
#endif // MAINWINDOW_H
