#include "Worker.hpp"

#include <iostream>
#include <chrono>
#include <thread>

void qt_multithread::Worker::startWork(int arg1, int arg2) {
    std::cout << "Starting work ..." << std::endl;
    work_ = true;
    wait_ = false;
    resetWorker(arg1, arg2);
    int percentDone{0};

    while(work_.load()){
        if(wait_.load()){
            std::unique_lock<std::mutex> lk(mutex_);
            std::cout << "Wait pressed, waiting ..." << std::endl;
            cv_.wait(lk);
            std::cout << "Continuing work ..." << std::endl;
        }else{
            if(percentDone != 100){
                percentDone = doStep();

                emit statusReady(percentDone);
            }else{
                std::cout << "Work done ..." << std::endl;
                work_ = false;
            }
        }
    }

    emit resultReady(result_);
}

void qt_multithread::Worker::stopWork() {
    std::cout << "Stopping work ..." << std::endl;
    work_ = false;
    if(wait_.load()){
        wait_ = false;
        cv_.notify_one();
    }
}

int qt_multithread::Worker::doStep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    result_ = "Generic worker";
    std::cout << "I did step!" << std::endl;
    return 100;
}

void qt_multithread::Worker::pauseWork() {
    std::cout << "Pausing work ..." << std::endl;
    wait_ = true;
}

void qt_multithread::Worker::continueWork() {
    std::cout << "Resuming work ..." << std::endl;
    wait_ = false;
    cv_.notify_one();
}
