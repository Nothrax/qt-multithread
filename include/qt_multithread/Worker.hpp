#pragma once

#include <QObject>
#include <QThread>

namespace qt_multithread{
    class Worker : public QObject {
    Q_OBJECT
    public:
    signals:
        void resultReady(QString result){};

    public slots:
        void startWork();
        void stopWork();
        void pauseWork();
        void continueWork();

    private:
        std::atomic<bool> _work{true};
        std::atomic<bool> _wait{false};
        std::mutex _mutex;
        std::condition_variable _cv;

        virtual void doStep();

    };
}

