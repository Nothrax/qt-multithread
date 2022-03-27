#include <iostream>
#include "PrimeNumberWorker.hpp"

int qt_multithread::PrimeNumberWorker::doStep() {


    while(!primes_[actualStep_]){
        actualStep_++;
        if(actualStep_ > to_){
            return 100;
        }
    }

    if(actualStep_ > to_){
        return 100;
    }

    if(actualStep_ > maxTo_){
        for(uint64_t i = actualStep_; i <= to_; actualStep_++){
            if(primes_[actualStep_]){
                result_ += " " + QString::number(i);
            }
        }
        return 100;
    }

    if(actualStep_ > from_){
        result_ += " " + QString::number(actualStep_);
    }
    numberOfPrimesFound_++;
    int percentDone = (float)(((float)numberOfPrimesFound_) / ((float)howManyPrimesShouldBeFound_) * 100);
    if(percentDone > 99){
        percentDone = 99;
    }

    if(actualStep_ * actualStep_ > to_){
        actualStep_++;
        return percentDone;
    }


    for (unsigned long long i = actualStep_ * actualStep_; i <= to_; i += actualStep_) {
        primes_[i] = false;
    }

    actualStep_++;
    return percentDone;
}

void qt_multithread::PrimeNumberWorker::resetWorker(int arg1, int arg2) {
    from_ = arg1;
    to_ = arg2;
    actualStep_ = 2;
    primes_ = std::vector<bool>(arg2 + 1, true);
    result_ = "Prime worker, primes calculated from interval<" + QString::number(from_) + "," + QString::number(to_) + ">: ";
    numberOfPrimesFound_ = 0;
    howManyPrimesShouldBeFound_ = to_/log(to_);

    std::cout << "reseting worker to " << std::to_string(arg1) << " " << std::to_string(arg2) << std::endl;
}
