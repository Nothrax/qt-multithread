#pragma once

#include "Worker.hpp"

#define MAX_FACTORIAL 500

namespace qt_multithread{
    class FactorialWorker: public Worker {
    //public:
    //    explicit FactorialWorker(int factorial):_factorial(factorial){};
    private:
        int _factorial;
        int _step{1};
        int _res[MAX_FACTORIAL] = {1};
        int _resSize{1};

        int doStep() override;
        void resetWorker(int arg1, int arg2) override;
    };
}