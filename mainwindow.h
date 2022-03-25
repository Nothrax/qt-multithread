#pragma once

#include <QMainWindow>
#include <QThread>
#include <qt_multithread/Controller.hpp>


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    qt_multithread::Controller *_controller1;

};