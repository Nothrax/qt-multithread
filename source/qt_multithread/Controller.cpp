#include <qt_multithread/Controller.hpp>
#include <iostream>

namespace qt_multithread{
Controller::Controller(qt_multithread::Worker *worker) {
    //_worker = worker;
    worker->moveToThread(&_workerThread);

    connect(&_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::workerStart, worker, &qt_multithread::Worker::startWork);
    connect(this, &Controller::workerStop, worker, &qt_multithread::Worker::stopWork);
    connect(this, &Controller::workerContinue, worker, &qt_multithread::Worker::continueWork);
    connect(this, &Controller::workerPause, worker, &qt_multithread::Worker::pauseWork);
    connect(worker, &qt_multithread::Worker::resultReady, this, &Controller::handleWorkerResults);

    _workerThread.start();
}


void Controller::handleWorkerResults(QString result) {
    std::cout << result.toStdString() << std::endl;
}

    Controller::~Controller() {
        _workerThread.quit();
        _workerThread.wait();
    }
}
