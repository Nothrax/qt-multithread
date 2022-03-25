#include "mainwindow.h"
#include <QWidget>
#include <qt_multithread/Worker.hpp>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    auto worker = new qt_multithread::Worker();
    _controller1 = new qt_multithread::Controller(worker);


    _controller1->workerStart();
    std::cout << "1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    _controller1->workerPause();
    std::cout << "2" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    _controller1->workerContinue();
    std::cout << "3" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    _controller1->workerStop();
    std::cout << "4" << std::endl;

}

MainWindow::~MainWindow()
{
}

