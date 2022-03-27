#include <iostream>
#include "FactorialWorker.hpp"

int qt_multithread::FactorialWorker::doStep() {

    if(factorial_ < 2){
        result_ = "Factorial worker, factorial calculated from: " + QString::number(factorial_) + " result is: 1";
        return 100;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int carry = 0;

    for (int i=0; i < resSize_; i++)
    {
        int prod = res_[i] * step_ + carry;
        res_[i] = prod % 10;
        carry  = prod/10;
    }
    while (carry)
    {
        res_[resSize_] = carry % 10;
        carry = carry/10;
        resSize_++;
    }

    if(step_ == factorial_){
        result_ = "Factorial worker, factorial calculated from: " + QString::number(factorial_) + " result is: ";
        int spaceCounter = 0;
        for(int i = resSize_ - 1; i >= 0; i--){
            result_ += QString::number(res_[i]);
            if(spaceCounter > 40){
                result_+="\n";
                spaceCounter = 0;
            }
            spaceCounter++;
        }
        return 100;
    }

    int percentDone = (float)(((float)step_) / ((float)factorial_) * 100);
    if(percentDone == 100) percentDone--;
    step_++;
    return percentDone;
}

void qt_multithread::FactorialWorker::resetWorker(int arg1, int arg2) {
    std::cout << "reseting worker to " << std::to_string(arg1) << std::endl;
    factorial_ = arg1;
    res_[0] = 1;
    step_ = 1;
    resSize_ = 1;
}
