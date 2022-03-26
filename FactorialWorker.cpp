#include <iostream>
#include "FactorialWorker.hpp"

int qt_multithread::FactorialWorker::doStep() {

    if(_factorial < 2){
        _result = "Factorial worker, factorial calculated from: " + QString::number(_factorial) + " result is: 1";
        return 100;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int carry = 0;

    for (int i=0; i<_resSize; i++)
    {
        int prod = _res[i] * _step + carry;
        _res[i] = prod % 10;
        carry  = prod/10;
    }
    while (carry)
    {
        _res[_resSize] = carry % 10;
        carry = carry/10;
        _resSize++;
    }

    if(_step == _factorial){
        _result = "Factorial worker, factorial calculated from: " + QString::number(_factorial) + " result is: ";
        int spaceCounter = 0;
        for(int i = _resSize-1; i >=0;i--){
            _result += QString::number(_res[i]);
            if(spaceCounter > 40){
                _result+="\n";
                spaceCounter = 0;
            }
            spaceCounter++;
        }
        return 100;
    }

    int percentDone = (float)(((float)_step)/((float)_factorial)*100);
    if(percentDone == 100) percentDone--;
    _step++;
    return percentDone;
}

void qt_multithread::FactorialWorker::resetWorker(int arg1, int arg2) {
    std::cout << "reseting worker to " << std::to_string(arg1) << std::endl;
    _factorial = arg1;
    _res[0] = 1;
    _step = 1;
    _resSize = 1;
}
