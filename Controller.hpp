#pragma once
#include "Worker.hpp"

namespace qt_multithread{
    class Controller : public QObject {
        Q_OBJECT
        QThread _workerThread;
    public:
        explicit Controller(Worker *worker);
        ~Controller() override;
    signals:
        void workerStart();
        void sendWorkerResult(const QString& result);
        void sendWorkerStatus(float status);

    public slots:
        void handleWorkerResults(const QString& result);
        void handleWorkerStatus(float status);
        void workerStop();
        void workerPause();
        void workerContinue();

    private:
        Worker *_worker;

    };
}
