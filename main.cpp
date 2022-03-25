#include <iostream>
#include <qt_multithread/PrimeNumberWorker.hpp>
#include <qt_multithread/FactorialWorker.hpp>
#include <qt_multithread/Worker.hpp>

int main(int argc, char** argv){
    qt_multithread::Worker worker;
    worker.startWork();
    worker.pauseWork();
    worker.continueWork();
    worker.stopWork();

    std::cout << "Let's go" << std::endl;
    return EXIT_SUCCESS;
}