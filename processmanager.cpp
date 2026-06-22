#include "processmanager.h"

#include <QtConcurrent>
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>

ProcessManager::ProcessManager(QObject *parent)
    : QObject(parent)
{
    m_senderProcess = nullptr;

    connect(&m_watcher,
            &QFutureWatcher<QVector<Target>>::finished,
            this,
            [this]()
            {
                QVector<Target> result = m_watcher.result();

                // qDebug() << "WATCHER RESULT:" << result.size();

                emit targetsProcessed(result);
            });
}

void ProcessManager::startSender(int targetCount)
{
    if (m_senderProcess &&
        m_senderProcess->state() != QProcess::NotRunning)
    {
        return;
    }

    if (!m_senderProcess)
    {
        m_senderProcess = new QProcess(this);
    }

    QString program = "python";

    QString script =
        QCoreApplication::applicationDirPath()
        + "/sender.py";

    QStringList args;

    args
        << script
        << QString::number(targetCount);

    m_senderProcess->start(program, args);
}

void ProcessManager::stopSender()
{
    if (!m_senderProcess)
        return;

    if (m_senderProcess->state() == QProcess::NotRunning)
        return;

    m_senderProcess->kill();

    m_senderProcess->waitForFinished();
}

void ProcessManager::processData(const QByteArray &data)
{
    if (m_watcher.isRunning())
        return;

    // Copy dữ liệu để tránh bị clear ở thread khác
    QByteArray dataCopy = data;

    auto future =
        QtConcurrent::run(
            [this, dataCopy]()
            {
                return parseTargets(dataCopy);
            });

    m_watcher.setFuture(future);
}

QVector<Target> ProcessManager::parseTargets(
    const QByteArray &data)
{
    QVector<Target> targets;

    // qDebug().noquote() << "RAW DATA:\n" << data;

    QString text =
        QString::fromUtf8(data);

    QStringList lines =
        text.split(
            '\n',
            Qt::SkipEmptyParts);

    //qDebug() << "LINES:"  << lines.size();

    for (const QString &line : lines)
    {
        //qDebug() << "LINE =" << line;

        QStringList parts =
            line.split(
                ' ',
                Qt::SkipEmptyParts);

        //qDebug() << "PARTS =" << parts;

        if (parts.size() < 3)
            continue;

        bool ok1;
        bool ok2;
        bool ok3;

        Target t;

        t.id =
            parts[0].toInt(&ok1);

        t.x =
            parts[1].toFloat(&ok2);

        t.y =
            parts[2].toFloat(&ok3);

        t.visible = true;

        if (!ok1 || !ok2 || !ok3)
            continue;

        targets.append(t);

        // qDebug() << "TARGET:" << t.id << t.x << t.y;
    }

    // qDebug() << "PARSED TARGETS:" << targets.size();

    return targets;
}