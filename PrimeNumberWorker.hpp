#pragma once

#include "Worker.hpp"

#include <cmath>

namespace qt_multithread{
    class PrimeNumberWorker: public Worker {
    private:
        int from_;
        int to_;
        uint64_t actualStep_;
        uint64_t maxTo_{(uint64_t)sqrt(UINT64_MAX - 1)};
        uint64_t numberOfPrimesFound_;
        uint64_t howManyPrimesShouldBeFound_;

        std::vector<bool> primes_;

        int doStep() override;
        void resetWorker(int arg1, int arg2) override;
    };
}


