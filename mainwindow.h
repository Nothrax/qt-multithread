#pragma once

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
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
    QLabel *_primeStateLabel;
    QLabel *_factorialStateLabel;

    QPushButton *_primeStart;
    QPushButton *_factorialStart;

    QPushButton *_primeStop;
    QPushButton *_factorialStop;

    QPushButton *_primePause;
    QPushButton *_factorialPause;

    QPushButton *_primeContinue;
    QPushButton *_factorialContinue;

    QProgressBar *_primeProgressBar;
    QProgressBar *_factorialProgressBar;

    int _primeStatus;
    int _factorialStatus;
};