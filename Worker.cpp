#include "Worker.hpp"

#include <iostream>
#include <chrono>
#include <thread>

void qt_multithread::Worker::startWork(int arg1, int arg2) {
    std::cout << "Starting work ..." << std::endl;
    _work = true;
    _wait = false;
    resetWorker(arg1, arg2);
    int percentDone{0};

    while(_work.load()){
        if(_wait.load()){
            std::unique_lock<std::mutex> lk(_mutex);
            std::cout << "Wait pressed, waiting ..." << std::endl;
            _cv.wait(lk);
            std::cout << "Continuing work ..." << std::endl;
        }else{
            if(percentDone != 100){
                percentDone = doStep();

                emit statusReady(percentDone);
            }else{
                std::cout << "Work done ..." << std::endl;
                _work = false;
            }
        }
    }

    emit resultReady(_result);
}

void qt_multithread::Worker::stopWork() {
    std::cout << "Stopping work ..." << std::endl;
    _work = false;
    if(_wait.load()){
        _wait = false;
        _cv.notify_one();
    }
}

int qt_multithread::Worker::doStep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    _result = "Generic worker";
    std::cout << "I did step!" << std::endl;
    return 100;
}

void qt_multithread::Worker::pauseWork() {
    std::cout << "Pausing work ..." << std::endl;
    _wait = true;
}

void qt_multithread::Worker::continueWork() {
    std::cout << "Resuming work ..." << std::endl;
    _wait = false;
    _cv.notify_one();
}
