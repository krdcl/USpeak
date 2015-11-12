#include "clienttcp.h"


quint16 ClientTcp::getPort() const
{
    return port;
}

void ClientTcp::setPort(const quint16 &value)
{
    port = value;
}

QHostAddress ClientTcp::getHostAdress() const
{
    return host_adress;
}

void ClientTcp::setHostAdress(const QHostAddress &value)
{
    host_adress = value;
}

ClientTcp::ClientTcp(QObject *parent) : QTcpSocket(parent)
{
    host_adress = QHostAddress::Any;
    port = 9999;
    time_out_wait = 300;
    connect(this, SIGNAL(readyRead()),this, SLOT( readMessage() ));

}

void ClientTcp::readMessage()
{
     QTcpSocket *socket = (QTcpSocket*)sender();
    qDebug() << "Reading: " << this->bytesAvailable();
    QByteArray message = socket->readAll();

    emit receivedMessage(message);
}

bool ClientTcp::writeMessage(QByteArray message)
{
    this->write(message);
    emit sendedMessage(message);
    if (!this->waitForBytesWritten(time_out_wait))
        return false;
    if (!this->waitForReadyRead(time_out_wait))
        return false;
    return true;
}

ClientTcp::~ClientTcp()
{
    this->close();
}

bool ClientTcp::connectToHostPort()
{
    connectToHost(host_adress, port);
return true;
    if(waitForConnected(time_out_wait))
    {
        return true;
    }
    else
    {
        this->close();
        qDebug() << "Not connected!";
        return false;
    }
}

