#include "Controller.hpp"
#include <iostream>

namespace qt_multithread{
Controller::Controller(qt_multithread::Worker *worker) {
    _worker = worker;
    worker->moveToThread(&_workerThread);

    connect(&_workerThread, &QThread::finished, _worker, &QObject::deleteLater);
    connect(this, &Controller::workerStart, _worker, &qt_multithread::Worker::startWork);
    connect(_worker, &qt_multithread::Worker::resultReady, this, &Controller::handleWorkerResults);
    connect(_worker, &qt_multithread::Worker::statusReady, this, &Controller::handleWorkerStatus);

    _workerThread.start();
}


void Controller::handleWorkerResults(const QString& result) {
    emit sendWorkerResult(result);
}

    Controller::~Controller() {
        _workerThread.quit();
        _workerThread.wait();
    }

    void Controller::workerStop() {
        _worker->stopWork();
    }

    void Controller::workerPause() {
        _worker->pauseWork();
    }

    void Controller::workerContinue() {
        _worker->continueWork();
    }

    void Controller::handleWorkerStatus(float status) {
        emit sendWorkerStatus(status);
    }

}
