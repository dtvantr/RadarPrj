#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "processmanager.h"

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);

    void startServer(quint16 port);

signals:
    void targetsParsed(const QVector<Target> &targets);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    QTcpServer *m_server;
    QTcpSocket *m_socket;

    QByteArray m_buffer;

    ProcessManager *m_processManager;
};