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
    controllerPrime_ = new qt_multithread::Controller(primeWorker);
    connect(controllerPrime_, &qt_multithread::Controller::sendWorkerResult, this, &MainWindow::handlePrimeResults);
    connect(controllerPrime_, &qt_multithread::Controller::sendWorkerStatus, this, &MainWindow::handlePrimeStatus);

    auto factorialWorker = new qt_multithread::FactorialWorker;
    controllerFactorial_ = new qt_multithread::Controller(factorialWorker);
    connect(controllerFactorial_, &qt_multithread::Controller::sendWorkerResult, this, &MainWindow::handleFactorialResults);
    connect(controllerFactorial_, &qt_multithread::Controller::sendWorkerStatus, this, &MainWindow::handleFactorialStatus);


    primeLabel_ = new QLabel{"Prime worker: stopped", this};
    primeLabel_->setGeometry(0, 0, 400, 40);
    primeLabel_->setAlignment(Qt::AlignCenter);
    primeStartButton_ = new QPushButton("start", this);
    primeStartButton_->setGeometry(QRect(QPoint(0, 40),
                                         QSize(100, 40)));
    connect(primeStartButton_, SIGNAL (released()), this, SLOT (primeStart()));

    primeStopButton_ = new QPushButton("stop", this);
    primeStopButton_->setGeometry(QRect(QPoint(100, 40),
                                        QSize(100, 40)));
    connect(primeStopButton_, SIGNAL (released()), this, SLOT (primeStop()));
    primeStopButton_->setEnabled(false);

    primePauseButton_ = new QPushButton("pause", this);
    primePauseButton_->setGeometry(QRect(QPoint(200, 40),
                                         QSize(100, 40)));
    connect(primePauseButton_, SIGNAL (released()), this, SLOT (primePause()));
    primePauseButton_->setEnabled(false);

    primeContinueButton_ = new QPushButton("continue", this);
    primeContinueButton_->setGeometry(QRect(QPoint(300, 40),
                                            QSize(100, 40)));
    connect(primeContinueButton_, SIGNAL (released()), this, SLOT (primeContinue()));
    primeContinueButton_->setEnabled(false);

    primeProgressBarButton_ = new QProgressBar(this);
    primeProgressBarButton_->setGeometry(QRect(QPoint(0, 80),
                                               QSize(400, 40)));
    primeProgressBarButton_->setRange(0, 100);
    primeProgressBarButton_->setValue(0);

    primeMinEditLabel_ = new QLabel("From: ", this);
    primeMinEditLabel_->setGeometry(QRect(QPoint(0, 120),
                                          QSize(100, 40)));
    primeMinEditLabel_->setAlignment(Qt::AlignCenter);

    primeMaxEditLabel_ = new QLabel("To: ", this);
    primeMaxEditLabel_->setGeometry(QRect(QPoint(200, 120),
                                          QSize(100, 40)));
    primeMaxEditLabel_->setAlignment(Qt::AlignCenter);

    primeMinEdit_ = new QLineEdit(this);
    primeMinEdit_->setGeometry(QRect(QPoint(100, 120),
                                     QSize(100, 40)));
    primeMinEdit_->setText("0");
    primeMinEdit_->setAlignment(Qt::AlignCenter);
    primeMinEdit_->setValidator(new QIntValidator(0, INT32_MAX, this) );

    primeMaxEdit_ = new QLineEdit(this);
    primeMaxEdit_->setGeometry(QRect(QPoint(300, 120),
                                     QSize(100, 40)));
    primeMaxEdit_->setText("0");
    primeMaxEdit_->setAlignment(Qt::AlignCenter);
    primeMaxEdit_->setValidator(new QIntValidator(0, INT32_MAX, this) );


    primeOutputLabel_ = new QLabel("Prime output", this);
    primeOutputLabel_->setGeometry(0, 160, 400, 440);
    primeOutputLabel_->setStyleSheet("QLabel { background-color : red; color : blue; }");
    primeOutputLabel_->setAlignment(Qt::AlignHCenter);

    ///factorial layout

    factorialLabel_ = new QLabel{"Factorial worker: stopped", this};
    factorialLabel_->setGeometry(400, 0, 450, 40);
    factorialLabel_->setAlignment(Qt::AlignCenter);

    factorialStartButton_ = new QPushButton("start", this);
    factorialStartButton_->setGeometry(QRect(QPoint(450, 40),
                                             QSize(100, 40)));
    connect(factorialStartButton_, SIGNAL (released()), this, SLOT (factorialStart()));
    factorialStopButton_ = new QPushButton("stop", this);
    factorialStopButton_->setGeometry(QRect(QPoint(550, 40),
                                            QSize(100, 40)));
    connect(factorialStopButton_, SIGNAL (released()), this, SLOT (factorialStop()));
    factorialStopButton_->setEnabled(false);

    factorialPauseButton_ = new QPushButton("pause", this);
    factorialPauseButton_->setGeometry(QRect(QPoint(650, 40),
                                             QSize(100, 40)));
    connect(factorialPauseButton_, SIGNAL (released()), this, SLOT (factorialPause()));
    factorialPauseButton_->setEnabled(false);

    factorialContinueButton_ = new QPushButton("continue", this);
    factorialContinueButton_->setGeometry(QRect(QPoint(750, 40),
                                                QSize(100, 40)));
    connect(factorialContinueButton_, SIGNAL (released()), this, SLOT (factorialContinue()));
    factorialContinueButton_->setEnabled(false);

    factorialProgressBarButton_ = new QProgressBar(this);
    factorialProgressBarButton_->setGeometry(QRect(QPoint(450, 80),
                                                   QSize(400, 40)));
    factorialProgressBarButton_->setRange(0, 100);
    factorialProgressBarButton_->setValue(0);

    factorialEditLabel_ = new QLabel("Factorial number: ", this);
    factorialEditLabel_->setGeometry(QRect(QPoint(450, 120),
                                           QSize(200, 40)));
    factorialEditLabel_->setAlignment(Qt::AlignCenter);

    factorialEdit_ = new QLineEdit(this);
    factorialEdit_->setGeometry(QRect(QPoint(650, 120),
                                      QSize(200, 40)));
    factorialEdit_->setText("0");
    factorialEdit_->setAlignment(Qt::AlignCenter);
    factorialEdit_->setValidator(new QIntValidator(1, INT16_MAX, this) );

    factorialOutputLabel_ = new QLabel("Factorial output", this);
    factorialOutputLabel_->setGeometry(450, 160, 400, 440);
    factorialOutputLabel_->setStyleSheet("QLabel { background-color : blue; color : red; }");
    factorialOutputLabel_->setAlignment(Qt::AlignHCenter);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handlePrimeResults(const QString& result) {
    std::cout << result.toStdString() << std::endl;
    primeOutputLabel_->setText(result);
    primeOutputLabel_->setWordWrap(true);

    primeStartButton_->setEnabled(true);
    primeStopButton_->setEnabled(false);
    primePauseButton_->setEnabled(false);
    primeContinueButton_->setEnabled(false);
    if(primeStatus_ > 99){
        primeLabel_->setText("Prime worker: Done!");
    }
}

void MainWindow::handleFactorialResults(const QString& result) {
    std::cout << result.toStdString() << std::endl;
    factorialOutputLabel_->setWordWrap(true);
    factorialOutputLabel_->setText(result);
    factorialStartButton_->setEnabled(true);
    factorialStopButton_->setEnabled(false);
    factorialPauseButton_->setEnabled(false);
    factorialContinueButton_->setEnabled(false);
    if(factorialStatus_ > 99){
        factorialLabel_->setText("Factorial worker: Done!");
    }

}

void MainWindow::primeStart() {
    if(primeMinEdit_->text().toInt() > primeMaxEdit_->text().toInt()){
        QMessageBox messageBox;
        messageBox.critical(this,"Error","From must be smaller than to!");
        messageBox.setFixedSize(100,100);
    }else{
        controllerPrime_->workerStart(primeMinEdit_->text().toInt(), primeMaxEdit_->text().toInt());
        primeStartButton_->setEnabled(false);
        primeStopButton_->setEnabled(true);
        primePauseButton_->setEnabled(true);
        primeContinueButton_->setEnabled(false);
        primeLabel_->setText("Prime worker: Calculating");
        primeProgressBarButton_->setValue(0);
    }
}

void MainWindow::primeStop() {
    controllerPrime_->workerStop();
    primeStartButton_->setEnabled(true);
    primeStopButton_->setEnabled(false);
    primePauseButton_->setEnabled(false);
    primeContinueButton_->setEnabled(false);
    primeLabel_->setText("Prime worker: Stopped");
    primeProgressBarButton_->setValue(0);
}

void MainWindow::primePause() {
    controllerPrime_->workerPause();
    primeStartButton_->setEnabled(false);
    primeStopButton_->setEnabled(true);
    primePauseButton_->setEnabled(false);
    primeContinueButton_->setEnabled(true);
    primeLabel_->setText("Prime worker: Paused");
}

void MainWindow::primeContinue() {
    controllerPrime_->workerContinue();
    primeStartButton_->setEnabled(false);
    primeStopButton_->setEnabled(true);
    primePauseButton_->setEnabled(true);
    primeContinueButton_->setEnabled(false);
    primeLabel_->setText("Prime worker: Calculating");
}

void MainWindow::factorialStart() {
    if(factorialEdit_->text().toInt() > MAX_FACTORIAL){
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Maximum factorial size supported is " + QString::number(MAX_FACTORIAL));
        messageBox.setFixedSize(100,100);
    }else{
        controllerFactorial_->workerStart(factorialEdit_->text().toInt(), 0);
        factorialStartButton_->setEnabled(false);
        factorialStopButton_->setEnabled(true);
        factorialPauseButton_->setEnabled(true);
        factorialContinueButton_->setEnabled(false);
        factorialLabel_->setText("Factorial worker: Calculating");
        factorialProgressBarButton_->setValue(0);
    }
}

void MainWindow::factorialStop() {
    controllerFactorial_->workerStop();
    factorialStartButton_->setEnabled(true);
    factorialStopButton_->setEnabled(false);
    factorialPauseButton_->setEnabled(false);
    factorialContinueButton_->setEnabled(false);
    factorialLabel_->setText("Factorial worker: Stopped");
    factorialProgressBarButton_->setValue(0);
}

void MainWindow::factorialPause() {
    controllerFactorial_->workerPause();
    factorialStartButton_->setEnabled(false);
    factorialStopButton_->setEnabled(true);
    factorialPauseButton_->setEnabled(false);
    factorialContinueButton_->setEnabled(true);
    factorialLabel_->setText("Factorial worker: Paused");
}

void MainWindow::factorialContinue() {
    controllerFactorial_->workerContinue();
    factorialStartButton_->setEnabled(false);
    factorialStopButton_->setEnabled(true);
    factorialPauseButton_->setEnabled(true);
    factorialContinueButton_->setEnabled(false);
    factorialLabel_->setText("Factorial worker: Calculating");
}

void MainWindow::handlePrimeStatus(float status) {
    //std::cout << "prime status = " << status << std::endl;
    primeStatus_ = status;
    primeProgressBarButton_->setValue(status);
}

void MainWindow::handleFactorialStatus(float status) {
    std::cout << "factorial status = " << status << std::endl;
    factorialStatus_ = status;
    factorialProgressBarButton_->setValue(status);
}


