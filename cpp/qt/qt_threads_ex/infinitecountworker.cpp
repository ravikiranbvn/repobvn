#include <QApplication>

#include "infinitecountworker.h"
#include "portablesleep.h"

InfiniteCountWorker::InfiniteCountWorker()
    : m_running(true)
{
}

void InfiniteCountWorker::doWork()
{
    int i = 0;
    while (m_running) {
        emit updateCount(i);
        i++;
        qApp->processEvents();
        PortableSleep::msleep(1000);
    }
    emit finished();
}

void InfiniteCountWorker::stopWork()
{
    m_running = false;
}
