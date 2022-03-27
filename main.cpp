#include "mainwindow.h"
#include <QApplication>

int main(int argc, char** argv){
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setFixedSize(850,600);
    mainWindow.show();

    return QApplication::exec();
}