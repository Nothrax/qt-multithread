#pragma once
#include "Worker.hpp"

namespace qt_multithread{
    class Controller : public QObject {
        Q_OBJECT
        QThread workerThread_;
    public:
        explicit Controller(Worker *worker);
        ~Controller();
    signals:
        void workerStart(int arg1, int arg2);
        void sendWorkerResult(const QString& result);
        void sendWorkerStatus(float status);

    public slots:
        void handleWorkerResults(const QString& result);
        void handleWorkerStatus(float status);
        void workerStop();
        void workerPause();
        void workerContinue();

    private:
        Worker *worker_;

    };
}
