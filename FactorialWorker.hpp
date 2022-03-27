#pragma once

#include "Worker.hpp"

#define MAX_FACTORIAL 1000

namespace qt_multithread{
    class FactorialWorker: public Worker {
    private:
        int factorial_;
        int step_{1};
        int res_[MAX_FACTORIAL] = {1};
        int resSize_{1};

        int doStep() override;
        void resetWorker(int arg1, int arg2) override;
    };
}