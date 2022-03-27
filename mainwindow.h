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
    qt_multithread::Controller *controllerPrime_;
    qt_multithread::Controller *controllerFactorial_;

    QLabel *primeLabel_;
    QLabel *factorialLabel_;
    QLabel *primeOutputLabel_;
    QLabel *factorialOutputLabel_;

    QLabel *factorialEditLabel_;
    QLineEdit *factorialEdit_;

    QLabel *primeMinEditLabel_;
    QLabel *primeMaxEditLabel_;
    QLineEdit *primeMinEdit_;
    QLineEdit *primeMaxEdit_;

    QPushButton *primeStartButton_;
    QPushButton *factorialStartButton_;

    QPushButton *primeStopButton_;
    QPushButton *factorialStopButton_;

    QPushButton *primePauseButton_;
    QPushButton *factorialPauseButton_;

    QPushButton *primeContinueButton_;
    QPushButton *factorialContinueButton_;

    QProgressBar *primeProgressBarButton_;
    QProgressBar *factorialProgressBarButton_;

    int primeStatus_;
    int factorialStatus_;
};