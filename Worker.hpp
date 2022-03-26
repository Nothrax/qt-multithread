#pragma once

#include <QObject>
#include <QThread>

namespace qt_multithread{
    class Worker : public QObject {
    Q_OBJECT
    public:
    signals:
        void resultReady(QString result);
        void statusReady(float status);

    public slots:
        void startWork(int arg1, int arg2);
        void stopWork();
        void pauseWork();
        void continueWork();

    private:
        std::atomic<bool> _work{true};
        std::atomic<bool> _wait{false};
        std::mutex _mutex;
        std::condition_variable _cv;

    protected:
        QString _result;

        virtual void resetWorker(int arg1, int arg2){};
        virtual int doStep();

    };
}

