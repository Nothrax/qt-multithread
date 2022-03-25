#pragma once

namespace qt_multithread{
    class Worker {
    public:
        void startWork();
        void stopWork();
        void pauseWork();
        void continueWork();
    private:
        virtual void doStep();
    };
}

