#include <ut/throwf.hxx>
#include "messageserver.h"

MessageServer::MessageServer(quint16 p_port, QObject *parent) : QObject(parent)
{
    // Setup signals
    connect(&m_Server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!m_Server.listen(QHostAddress::Any, p_port))
            ut::throwf<::std::runtime_error>("Failed to bind to port %d!", p_port);
}

MessageServer::~MessageServer()
{
    // Close all sockets
    for(auto t_sock: m_Buffers.keys())
    {
        t_sock->close();
        t_sock->deleteLater();
    }

    m_Server.close();
}

void MessageServer::newConnection()
{
    while(m_Server.hasPendingConnections())
    {
        auto t_sock = m_Server.nextPendingConnection();

        // Connect signals
        connect(t_sock, SIGNAL(disconnected()),
                this, SLOT(clientDisconnected()));

        connect(t_sock, SIGNAL(readyRead()),
                this, SLOT(dataAvailable()));

        // Add new buffer to map
        m_Buffers.insert(t_sock, QByteArray{});
    }

    emit clientConnected();
}

void MessageServer::clientDisconnected()
{
    // Retrieve socket that got disconnected
    auto t_sock = static_cast<QTcpSocket*>(sender());

    // Remove buffer
    m_Buffers.remove(t_sock);

    // Schedule socket to be deleted when possible
    t_sock->deleteLater();
}

void MessageServer::dataAvailable()
{
    // Retrieve socket and buffer
    auto t_sock = static_cast<QTcpSocket*>(sender());
    auto& t_buf = m_Buffers[t_sock];

    // Prepare empty message
    Message t_msg;

    // Read as much data as possible
    while(t_sock->bytesAvailable() > 0)
    {
        // Append data
        t_buf.append(t_sock->readAll());

        // Read as many messages as possible
        while(t_msg.tryParse(t_buf))
            emit messageReceived(t_msg);
    }
}
