#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QVector>
#include <QFutureWatcher>
#include <QProcess>

#include "target.h"

class ProcessManager : public QObject
{
    Q_OBJECT

public:
    explicit ProcessManager(QObject *parent = nullptr);

    Q_INVOKABLE void startSender(int targetCount);
    Q_INVOKABLE void stopSender();

public slots:
    void processData(const QByteArray &data);

signals:
    void targetsProcessed(const QVector<Target> &targets);

private:
    QVector<Target> parseTargets(const QByteArray &data);

private:
    QFutureWatcher<QVector<Target>> m_watcher;

    QProcess *m_senderProcess;
};

#endif