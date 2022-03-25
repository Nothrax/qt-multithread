#include "mainwindow.h"
#include <QWidget>
#include "Worker.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    auto workerPrime = new qt_multithread::Worker();
    _controllerPrime = new qt_multithread::Controller(workerPrime);
    connect(_controllerPrime, &qt_multithread::Controller::sendWorkerResult, this, &MainWindow::handlePrimeResults);
    connect(_controllerPrime, &qt_multithread::Controller::sendWorkerStatus, this, &MainWindow::handlePrimeStatus);

    auto workerFactorial = new qt_multithread::Worker();
    _controllerFactorial = new qt_multithread::Controller(workerFactorial);
    connect(_controllerFactorial, &qt_multithread::Controller::sendWorkerResult, this, &MainWindow::handleFactorialResults);
    connect(_controllerFactorial, &qt_multithread::Controller::sendWorkerStatus, this, &MainWindow::handleFactorialStatus);

    _primeLabel = new QLabel{"Prime worker", this};
    _factorialLabel = new QLabel{"Factorial worker", this};
    _primeLabel->setGeometry(0, 0,100, 40);
    _factorialLabel->setGeometry(0, 40,100, 40);

    _primeStart = new QPushButton("start",this);
    _factorialStart = new QPushButton("start",this);
    _primeStart->setGeometry(QRect(QPoint(100, 0),
                                            QSize(60, 40)));
    _factorialStart->setGeometry(QRect(QPoint(100, 40),
                                   QSize(60, 40)));
    connect(_primeStart, SIGNAL (released()), this, SLOT (primeStart()));
    connect(_factorialStart, SIGNAL (released()), this, SLOT (factorialStart()));

    _primeStop = new QPushButton("stop",this);
    _factorialStop = new QPushButton("stop",this);
    _primeStop->setGeometry(QRect(QPoint(160, 0),
                                   QSize(60, 40)));
    _factorialStop->setGeometry(QRect(QPoint(160, 40),
                                       QSize(60, 40)));
    connect(_primeStop, SIGNAL (released()), this, SLOT (primeStop()));
    connect(_factorialStop, SIGNAL (released()), this, SLOT (factorialStop()));
    _primeStop->setEnabled(false);
    _factorialStop->setEnabled(false);

    _primePause = new QPushButton("pause",this);
    _factorialPause = new QPushButton("pause",this);
    _primePause->setGeometry(QRect(QPoint(220, 0),
                                  QSize(60, 40)));
    _factorialPause->setGeometry(QRect(QPoint(220, 40),
                                      QSize(60, 40)));
    connect(_primePause, SIGNAL (released()), this, SLOT (primePause()));
    connect(_factorialPause, SIGNAL (released()), this, SLOT (factorialPause()));
    _primePause->setEnabled(false);
    _factorialPause->setEnabled(false);

    _primeContinue = new QPushButton("continue",this);
    _factorialContinue = new QPushButton("continue",this);
    _primeContinue->setGeometry(QRect(QPoint(280, 0),
                                   QSize(80, 40)));
    _factorialContinue->setGeometry(QRect(QPoint(280, 40),
                                       QSize(80, 40)));
    connect(_primeContinue, SIGNAL (released()), this, SLOT (primeContinue()));
    connect(_factorialContinue, SIGNAL (released()), this, SLOT (factorialContinue()));
    _primeContinue->setEnabled(false);
    _factorialContinue->setEnabled(false);

    _primeStateLabel = new QLabel{"stopped", this};
    _factorialStateLabel = new QLabel{"stopped", this};
    _primeStateLabel->setGeometry(360, 0,100, 40);
    _factorialStateLabel->setGeometry(360, 40,100, 40);

    _primeProgressBar = new QProgressBar(this);
    _primeProgressBar->setGeometry(QRect(QPoint(460, 0),
                                         QSize(300, 40)));
    _primeProgressBar->setRange(0,100);
    _primeProgressBar->setValue(0);

    _factorialProgressBar = new QProgressBar(this);
    _factorialProgressBar->setGeometry(QRect(QPoint(460, 40),
                                         QSize(300, 40)));
    _factorialProgressBar->setRange(0,100);
    _factorialProgressBar->setValue(0);

}

MainWindow::~MainWindow()
{

}

void MainWindow::handlePrimeResults(const QString& result) {
    std::cout << result.toStdString() << std::endl;
    _primeStart->setEnabled(true);
    _primeStop->setEnabled(false);
    _primePause->setEnabled(false);
    _primeContinue->setEnabled(false);
    if(_primeStatus > 99){
        _primeStateLabel->setText("Done!");
    }
}

void MainWindow::handleFactorialResults(const QString& result) {
    std::cout << result.toStdString() << std::endl;
    _factorialStart->setEnabled(true);
    _factorialStop->setEnabled(false);
    _factorialPause->setEnabled(false);
    _factorialContinue->setEnabled(false);
    _factorialStateLabel->setText("Done!");
    if(_factorialStatus > 99){
        _factorialStateLabel->setText("Done!");
    }

}

void MainWindow::primeStart() {
    _controllerPrime->workerStart();
    _primeStart->setEnabled(false);
    _primeStop->setEnabled(true);
    _primePause->setEnabled(true);
    _primeContinue->setEnabled(false);
    _primeStateLabel->setText("Calculating");
    _primeProgressBar->setValue(0);
}

void MainWindow::primeStop() {
    _controllerPrime->workerStop();
    _primeStart->setEnabled(true);
    _primeStop->setEnabled(false);
    _primePause->setEnabled(false);
    _primeContinue->setEnabled(false);
    _primeStateLabel->setText("Stopped");

}

void MainWindow::primePause() {
    _controllerPrime->workerPause();
    _primeStart->setEnabled(false);
    _primeStop->setEnabled(true);
    _primePause->setEnabled(false);
    _primeContinue->setEnabled(true);
    _primeStateLabel->setText("Paused");
}

void MainWindow::primeContinue() {
    _controllerPrime->workerContinue();
    _primeStart->setEnabled(false);
    _primeStop->setEnabled(true);
    _primePause->setEnabled(true);
    _primeContinue->setEnabled(false);
    _primeStateLabel->setText("Calculating");
}

void MainWindow::factorialStart() {
    _controllerFactorial->workerStart();
    _factorialStart->setEnabled(false);
    _factorialStop->setEnabled(true);
    _factorialPause->setEnabled(true);
    _factorialContinue->setEnabled(false);
    _factorialStateLabel->setText("Calculating");
    _factorialProgressBar->setValue(0);
}

void MainWindow::factorialStop() {
    _controllerFactorial->workerStop();
    _factorialStart->setEnabled(true);
    _factorialStop->setEnabled(false);
    _factorialPause->setEnabled(false);
    _factorialContinue->setEnabled(false);
    _factorialStateLabel->setText("Stopped");
}

void MainWindow::factorialPause() {
    _controllerFactorial->workerPause();
    _factorialStart->setEnabled(false);
    _factorialStop->setEnabled(true);
    _factorialPause->setEnabled(false);
    _factorialContinue->setEnabled(true);
    _factorialStateLabel->setText("Paused");
}

void MainWindow::factorialContinue() {
    _controllerFactorial->workerContinue();
    _factorialStart->setEnabled(false);
    _factorialStop->setEnabled(true);
    _factorialPause->setEnabled(true);
    _factorialContinue->setEnabled(false);
    _factorialStateLabel->setText("Calculating");
}

void MainWindow::handlePrimeStatus(float status) {
    std::cout << "prime status = " << status << std::endl;
    _primeStatus = status;
    _primeProgressBar->setValue(status);
}

void MainWindow::handleFactorialStatus(float status) {
    std::cout << "factorial status = " << status << std::endl;
    _factorialStatus = status;
    _factorialProgressBar->setValue(status);
}


