#pragma once
#include <qt_multithread/Worker.hpp>

namespace qt_multithread{
    class Controller : public QObject {
        Q_OBJECT
        QThread _workerThread;
    public:
        explicit Controller(Worker *worker);
        ~Controller() override;
    signals:
        void workerStart(){};
        void workerStop(){};
        void workerPause(){};
        void workerContinue(){};

    public slots:
        void handleWorkerResults(QString result);

    private:
        Worker *_worker;

    };
}
