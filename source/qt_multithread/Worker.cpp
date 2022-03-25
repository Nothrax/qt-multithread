#include <qt_multithread/Worker.hpp>

#include <iostream>
#include <chrono>
#include <thread>

void qt_multithread::Worker::startWork() {
    std::cout << "Starting work ..." << std::endl;
    _work.store(true);
    int stepNumber = 0;
    int numberOfSteps = 5;

    while(_work.load()){
        if(_wait.load()){
            std::unique_lock<std::mutex> lk(_mutex);
            std::cout << "Wait pressed, waiting ..." << std::endl;
            _cv.wait(lk, []{return true;});
            std::cout << "Continuing work ..." << std::endl;
        }else{
            if(stepNumber < numberOfSteps){
                doStep();
                stepNumber++;
            }else{
                std::cout << "Work done ..." << std::endl;
                _work.store(false);
            }
        }
    }

    emit resultReady(QString(rand() % 1000));
}

void qt_multithread::Worker::stopWork() {
    std::cout << "Stopping work ..." << std::endl;
    _work.store(false);
    _wait.store(false);
}

void qt_multithread::Worker::doStep() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "I did step!" << std::endl;
}

void qt_multithread::Worker::pauseWork() {
    std::cout << "Pausing work ..." << std::endl;
    _wait.store(true);
}

void qt_multithread::Worker::continueWork() {
    std::cout << "Resuming work ..." << std::endl;
    _wait.store(false);
    _cv.notify_all();
}
