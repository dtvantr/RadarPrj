#include "networkmanager.h"

#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    m_server = new QTcpServer(this);

    m_socket = nullptr;

    m_processManager = new ProcessManager(this);

    connect(m_server,
            &QTcpServer::newConnection,
            this,
            &NetworkManager::onNewConnection);

    connect(m_processManager,
            &ProcessManager::targetsProcessed,
            this,
            &NetworkManager::targetsParsed);
}

void NetworkManager::startServer(quint16 port)
{
    bool success =
        m_server->listen(
            QHostAddress::Any,
            port);

    /*
    if(success)
    {
        qDebug() << "Server started on port"
        << port;
    }
    else
    {
        qDebug()
        << "Server failed:"
        << m_server->errorString();
    }
    */
}

void NetworkManager::onNewConnection()
{
    m_socket =
        m_server->nextPendingConnection();

    /* qDebug()
        << "Client connected"; */

    connect(m_socket,
            &QTcpSocket::readyRead,
            this,
            &NetworkManager::onReadyRead);

    connect(m_socket,
            &QTcpSocket::disconnected,
            this,
            &NetworkManager::onClientDisconnected);
}

void NetworkManager::onReadyRead()
{
    if(!m_socket)
        return;

    QByteArray data =
        m_socket->readAll();

    /*
    qDebug()
        << "TCP bytes:"
        << data.size();

    qDebug().noquote()
        << data;
    */

    // Gửi trực tiếp packet nhận được
    m_processManager->processData(data);
}

void NetworkManager::onClientDisconnected()
{
    qDebug()
    << "Client disconnected";

    m_socket->deleteLater();

    m_socket = nullptr;

    m_buffer.clear();
}