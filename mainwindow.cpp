#include "mainwindow.h"
#include <QWidget>
#include "Worker.hpp"
#include "PrimeNumberWorker.hpp"
#include "FactorialWorker.hpp"
#include <iostream>
#include <QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    auto primeWorker = new qt_multithread::PrimeNumberWorker;
    _controllerPrime = new qt_multithread::Controller(primeWorker);
    connect(_controllerPrime, &qt_multithread::Controller::sendWorkerResult, this, &MainWindow::handlePrimeResults);
    connect(_controllerPrime, &qt_multithread::Controller::sendWorkerStatus, this, &MainWindow::handlePrimeStatus);

    auto factorialWorker = new qt_multithread::FactorialWorker;
    _controllerFactorial = new qt_multithread::Controller(factorialWorker);
    connect(_controllerFactorial, &qt_multithread::Controller::sendWorkerResult, this, &MainWindow::handleFactorialResults);
    connect(_controllerFactorial, &qt_multithread::Controller::sendWorkerStatus, this, &MainWindow::handleFactorialStatus);


    _primeLabel = new QLabel{"Prime worker: stopped", this};
    _primeLabel->setGeometry(0, 0,400, 40);
    _primeLabel->setAlignment(Qt::AlignCenter);
    _primeStartButton = new QPushButton("start", this);
    _primeStartButton->setGeometry(QRect(QPoint(0, 40),
                                         QSize(100, 40)));
    connect(_primeStartButton, SIGNAL (released()), this, SLOT (primeStart()));

    _primeStopButton = new QPushButton("stop", this);
    _primeStopButton->setGeometry(QRect(QPoint(100, 40),
                                        QSize(100, 40)));
    connect(_primeStopButton, SIGNAL (released()), this, SLOT (primeStop()));
    _primeStopButton->setEnabled(false);

    _primePauseButton = new QPushButton("pause", this);
    _primePauseButton->setGeometry(QRect(QPoint(200, 40),
                                         QSize(100, 40)));
    connect(_primePauseButton, SIGNAL (released()), this, SLOT (primePause()));
    _primePauseButton->setEnabled(false);

    _primeContinueButton = new QPushButton("continue", this);
    _primeContinueButton->setGeometry(QRect(QPoint(300, 40),
                                            QSize(100, 40)));
    connect(_primeContinueButton, SIGNAL (released()), this, SLOT (primeContinue()));
    _primeContinueButton->setEnabled(false);

    _primeProgressBarButton = new QProgressBar(this);
    _primeProgressBarButton->setGeometry(QRect(QPoint(0, 80),
                                               QSize(400, 40)));
    _primeProgressBarButton->setRange(0, 100);
    _primeProgressBarButton->setValue(0);

    _primeMinEditLabel = new QLabel("From: ", this);
    _primeMinEditLabel->setGeometry(QRect(QPoint(0, 120),
                                           QSize(100, 40)));
    _primeMinEditLabel->setAlignment( Qt::AlignCenter);

    _primeMaxEditLabel = new QLabel("To: ", this);
    _primeMaxEditLabel->setGeometry(QRect(QPoint(200, 120),
                                          QSize(100, 40)));
    _primeMaxEditLabel->setAlignment( Qt::AlignCenter);

    _primeMinEdit = new QLineEdit(this);
    _primeMinEdit->setGeometry(QRect(QPoint(100, 120),
                                      QSize(100, 40)));
    _primeMinEdit->setText("0");
    _primeMinEdit->setAlignment( Qt::AlignCenter);
    _primeMinEdit->setValidator( new QIntValidator(0, INT16_MAX, this) );

    _primeMaxEdit = new QLineEdit(this);
    _primeMaxEdit->setGeometry(QRect(QPoint(300, 120),
                                     QSize(100, 40)));
    _primeMaxEdit->setText("0");
    _primeMaxEdit->setAlignment( Qt::AlignCenter);
    _primeMaxEdit->setValidator( new QIntValidator(0, INT16_MAX, this) );


    _primeOutputLabel = new QLabel("Prime output", this);
    _primeOutputLabel->setGeometry(0, 160,400, 440);
    _primeOutputLabel->setStyleSheet("QLabel { background-color : red; color : blue; }");
    _primeOutputLabel->setAlignment(Qt::AlignHCenter);

    ///factorial layout

    _factorialLabel = new QLabel{"Factorial worker: stopped", this};
    _factorialLabel->setGeometry(400, 0,450, 40);
    _factorialLabel->setAlignment(Qt::AlignCenter);

    _factorialStartButton = new QPushButton("start", this);
    _factorialStartButton->setGeometry(QRect(QPoint(450, 40),
                                             QSize(100, 40)));
    connect(_factorialStartButton, SIGNAL (released()), this, SLOT (factorialStart()));
    _factorialStopButton = new QPushButton("stop", this);
    _factorialStopButton->setGeometry(QRect(QPoint(550, 40),
                                            QSize(100, 40)));
    connect(_factorialStopButton, SIGNAL (released()), this, SLOT (factorialStop()));
    _factorialStopButton->setEnabled(false);

    _factorialPauseButton = new QPushButton("pause", this);
    _factorialPauseButton->setGeometry(QRect(QPoint(650, 40),
                                             QSize(100, 40)));
    connect(_factorialPauseButton, SIGNAL (released()), this, SLOT (factorialPause()));
    _factorialPauseButton->setEnabled(false);

    _factorialContinueButton = new QPushButton("continue", this);
    _factorialContinueButton->setGeometry(QRect(QPoint(750, 40),
                                                QSize(100, 40)));
    connect(_factorialContinueButton, SIGNAL (released()), this, SLOT (factorialContinue()));
    _factorialContinueButton->setEnabled(false);

    _factorialProgressBarButton = new QProgressBar(this);
    _factorialProgressBarButton->setGeometry(QRect(QPoint(450, 80),
                                                   QSize(400, 40)));
    _factorialProgressBarButton->setRange(0, 100);
    _factorialProgressBarButton->setValue(0);

    _factorialEditLabel = new QLabel("Factorial number: ", this);
    _factorialEditLabel->setGeometry(QRect(QPoint(450, 120),
                                           QSize(200, 40)));
    _factorialEditLabel->setAlignment( Qt::AlignCenter);

    _factorialEdit = new QLineEdit(this);
    _factorialEdit->setGeometry(QRect(QPoint(650, 120),
                                      QSize(200, 40)));
    _factorialEdit->setText("0");
    _factorialEdit->setAlignment( Qt::AlignCenter);
    _factorialEdit->setValidator( new QIntValidator(1, INT16_MAX, this) );

    _factorialOutputLabel = new QLabel("Factorial output", this);
    _factorialOutputLabel->setGeometry(450, 160,400, 440);
    _factorialOutputLabel->setStyleSheet("QLabel { background-color : blue; color : red; }");
    _factorialOutputLabel->setAlignment( Qt::AlignHCenter);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handlePrimeResults(const QString& result) {
    std::cout << result.toStdString() << std::endl;
    _primeOutputLabel->setText(result);
    _primeStartButton->setEnabled(true);
    _primeStopButton->setEnabled(false);
    _primePauseButton->setEnabled(false);
    _primeContinueButton->setEnabled(false);
    if(_primeStatus > 99){
        _primeLabel->setText("Prime worker: Done!");
    }
}

void MainWindow::handleFactorialResults(const QString& result) {
    std::cout << result.toStdString() << std::endl;
    _factorialOutputLabel->setWordWrap(true);
    _factorialOutputLabel->setText(result);
    _factorialStartButton->setEnabled(true);
    _factorialStopButton->setEnabled(false);
    _factorialPauseButton->setEnabled(false);
    _factorialContinueButton->setEnabled(false);
    if(_factorialStatus > 99){
        _factorialLabel->setText("Factorial worker: Done!");
    }

}

void MainWindow::primeStart() {
    if(_primeMinEdit->text().toInt() > _primeMaxEdit->text().toInt()){
        QMessageBox messageBox;
        messageBox.critical(this,"Error","From must be smaller than to!");
        messageBox.setFixedSize(100,100);
    }else{
        //auto workerPrime = new qt_multithread::PrimeNumberWorker();
        //_controllerPrime->setWorker(workerPrime);

        _controllerPrime->workerStart(_primeMinEdit->text().toInt(),_primeMaxEdit->text().toInt());
        _primeStartButton->setEnabled(false);
        _primeStopButton->setEnabled(true);
        _primePauseButton->setEnabled(true);
        _primeContinueButton->setEnabled(false);
        _primeLabel->setText("Prime worker: Calculating");
        _primeProgressBarButton->setValue(0);
    }
}

void MainWindow::primeStop() {
    _controllerPrime->workerStop();
    _primeStartButton->setEnabled(true);
    _primeStopButton->setEnabled(false);
    _primePauseButton->setEnabled(false);
    _primeContinueButton->setEnabled(false);
    _primeLabel->setText("Prime worker: Stopped");
    _primeProgressBarButton->setValue(0);
}

void MainWindow::primePause() {
    _controllerPrime->workerPause();
    _primeStartButton->setEnabled(false);
    _primeStopButton->setEnabled(true);
    _primePauseButton->setEnabled(false);
    _primeContinueButton->setEnabled(true);
    _primeLabel->setText("Prime worker: Paused");
}

void MainWindow::primeContinue() {
    _controllerPrime->workerContinue();
    _primeStartButton->setEnabled(false);
    _primeStopButton->setEnabled(true);
    _primePauseButton->setEnabled(true);
    _primeContinueButton->setEnabled(false);
    _primeLabel->setText("Prime worker: Calculating");
}

void MainWindow::factorialStart() {
    if(_factorialEdit->text().toInt() > MAX_FACTORIAL){
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Maximum factorial size supported is " + QString::number(MAX_FACTORIAL));
        messageBox.setFixedSize(100,100);
    }else{
        //auto workerFactorial = new qt_multithread::FactorialWorker(_factorialEdit->text().toInt());
        //_controllerFactorial->setWorker(workerFactorial);
        _controllerFactorial->workerStart(_factorialEdit->text().toInt(),0);
        _factorialStartButton->setEnabled(false);
        _factorialStopButton->setEnabled(true);
        _factorialPauseButton->setEnabled(true);
        _factorialContinueButton->setEnabled(false);
        _factorialLabel->setText("Factorial worker: Calculating");
        _factorialProgressBarButton->setValue(0);
    }
}

void MainWindow::factorialStop() {
    _controllerFactorial->workerStop();
    _factorialStartButton->setEnabled(true);
    _factorialStopButton->setEnabled(false);
    _factorialPauseButton->setEnabled(false);
    _factorialContinueButton->setEnabled(false);
    _factorialLabel->setText("Factorial worker: Stopped");
    _factorialProgressBarButton->setValue(0);
}

void MainWindow::factorialPause() {
    _controllerFactorial->workerPause();
    _factorialStartButton->setEnabled(false);
    _factorialStopButton->setEnabled(true);
    _factorialPauseButton->setEnabled(false);
    _factorialContinueButton->setEnabled(true);
    _factorialLabel->setText("Factorial worker: Paused");
}

void MainWindow::factorialContinue() {
    _controllerFactorial->workerContinue();
    _factorialStartButton->setEnabled(false);
    _factorialStopButton->setEnabled(true);
    _factorialPauseButton->setEnabled(true);
    _factorialContinueButton->setEnabled(false);
    _factorialLabel->setText("Factorial worker: Calculating");
}

void MainWindow::handlePrimeStatus(float status) {
    std::cout << "prime status = " << status << std::endl;
    _primeStatus = status;
    _primeProgressBarButton->setValue(status);
}

void MainWindow::handleFactorialStatus(float status) {
    std::cout << "factorial status = " << status << std::endl;
    _factorialStatus = status;
    _factorialProgressBarButton->setValue(status);
}


