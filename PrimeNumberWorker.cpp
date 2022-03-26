#include <iostream>
#include "PrimeNumberWorker.hpp"

int qt_multithread::PrimeNumberWorker::doStep() {
    _result = "Prime worker, primes calculated from interval<" + QString::number(_from) + "," + QString::number(_to) + ">" ;
    return 100;
}

void qt_multithread::PrimeNumberWorker::resetWorker(int arg1, int arg2) {
    _from = arg1;
    _to = arg2;

    std::cout << "reseting worker to" << std::to_string(arg1) << " " << std::to_string(arg2) << std::endl;
}
