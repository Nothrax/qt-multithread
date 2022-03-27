#include "Controller.hpp"
#include <iostream>

namespace qt_multithread {
    Controller::Controller(Worker *worker) {
        worker_ = worker;
        worker_->moveToThread(&workerThread_);

        connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);
        connect(this, &Controller::workerStart, worker_, &qt_multithread::Worker::startWork);
        connect(worker_, &qt_multithread::Worker::resultReady, this, &Controller::handleWorkerResults);
        connect(worker_, &qt_multithread::Worker::statusReady, this, &Controller::handleWorkerStatus);

        workerThread_.start();

    }


    void Controller::handleWorkerResults(const QString &result) {
        emit sendWorkerResult(result);
    }

    Controller::~Controller() {
        workerThread_.quit();
        workerThread_.wait();
    }

    void Controller::workerStop() {
        worker_->stopWork();
    }

    void Controller::workerPause() {
        worker_->pauseWork();
    }

    void Controller::workerContinue() {
        worker_->continueWork();
    }

    void Controller::handleWorkerStatus(float status) {
        emit sendWorkerStatus(status);
    }


}
