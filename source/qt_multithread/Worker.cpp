#include <qt_multithread/Worker.hpp>

#include <iostream>

void qt_multithread::Worker::startWork() {
    std::cout << "Starting work ..." << std::endl;
}

void qt_multithread::Worker::stopWork() {
    std::cout << "Stopping work ..." << std::endl;
}

void qt_multithread::Worker::doStep() {
    std::cout << "I did step!" << std::endl;
}

void qt_multithread::Worker::pauseWork() {
    std::cout << "Pausing work ..." << std::endl;
}

void qt_multithread::Worker::continueWork() {
    std::cout << "Resuming work ..." << std::endl;
}
