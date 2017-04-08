#ifndef MESSAGESERVER_H
#define MESSAGESERVER_H

#include <QObject>
#include <QByteArray>
#include <QTcpServer>
#include <QString>
#include <QTcpSocket>
#include <QMap>

#include "message.h"

class MessageServer : public QObject
{
    Q_OBJECT
public:
    explicit MessageServer(quint16 p_port, QObject *parent = 0);
    ~MessageServer();

signals:
    void messageReceived(Message p_msg);
    void clientConnected();

public slots:
    void newConnection();
    void clientDisconnected();
    void dataAvailable();


private:
    QMap<QTcpSocket*, QByteArray> m_Buffers;
    QTcpServer m_Server;
};

#endif // MESSAGESERVER_H
