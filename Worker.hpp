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
        std::atomic<bool> work_{true};
        std::atomic<bool> wait_{false};
        std::mutex mutex_;
        std::condition_variable cv_;

    protected:
        QString result_;

        virtual void resetWorker(int arg1, int arg2){};
        virtual int doStep();

    };
}

