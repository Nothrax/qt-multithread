#pragma once

#include "Worker.hpp"

namespace qt_multithread{
    class PrimeNumberWorker: public Worker {
    //public:
    //    PrimeNumberWorker(int from, int to):_from(from), _to(to){};
    private:
        int _from;
        int _to;

        int doStep() override;
        void resetWorker(int arg1, int arg2) override;
    };
}


