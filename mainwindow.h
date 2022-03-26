#pragma once

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>
#include "Controller.hpp"


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handlePrimeResults(const QString& result);
    void handleFactorialResults(const QString& result);

    void handlePrimeStatus(float status);
    void handleFactorialStatus(float status);

    void primeStart();
    void primeStop();
    void primePause();
    void primeContinue();

    void factorialStart();
    void factorialStop();
    void factorialPause();
    void factorialContinue();

private:
    qt_multithread::Controller *_controllerPrime;
    qt_multithread::Controller *_controllerFactorial;

    QLabel *_primeLabel;
    QLabel *_factorialLabel;
    QLabel *_primeOutputLabel;
    QLabel *_factorialOutputLabel;

    QLabel *_factorialEditLabel;
    QLineEdit *_factorialEdit;

    QLabel *_primeMinEditLabel;
    QLabel *_primeMaxEditLabel;
    QLineEdit *_primeMinEdit;
    QLineEdit *_primeMaxEdit;

    QPushButton *_primeStartButton;
    QPushButton *_factorialStartButton;

    QPushButton *_primeStopButton;
    QPushButton *_factorialStopButton;

    QPushButton *_primePauseButton;
    QPushButton *_factorialPauseButton;

    QPushButton *_primeContinueButton;
    QPushButton *_factorialContinueButton;

    QProgressBar *_primeProgressBarButton;
    QProgressBar *_factorialProgressBarButton;

    int _primeStatus;
    int _factorialStatus;
};