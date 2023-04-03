
#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

void setupDarkThemePalette() {
  qApp->setStyle(QStyleFactory::create("Fusion"));

  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button,QColor(88, 24, 69));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);

  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);

  qApp->setPalette(darkPalette);

  qApp->setStyleSheet(
      "QToolTip { color: #ffffff; background-color: #900C3F; "
                      "border: 1px solid #581845; }"
      "QPushButton:disabled {background-color:#353535;}"

      );
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  time_line::MainWindow w;
  setupDarkThemePalette();
  w.show();
  return a.exec();
}
