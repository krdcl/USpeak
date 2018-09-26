#include "servertcp.h"

//dev_one 10 27

ServerTCP::ServerTCP(QObject *parent) : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()),
            this, SLOT(newClient()));



    host_adress = QHostAddress::Any;
    port = 9999;
    time_out_wait = 300;
}

ServerTCP::~ServerTCP()
{
    foreach(QTcpSocket * cliento,clients)
        delete cliento;
}

void ServerTCP::newClient()
{
    // need to grab the socket
    QTcpSocket *socket = nextPendingConnection();

    clients.append(socket);

    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));


    socket->write("Hello client\r\n");
    //socket->flush();

    socket->waitForBytesWritten(time_out_wait);
}

bool ServerTCP::sendMessageToAllClients(QByteArray message)
{
    bool rezult = true;
    emit sendedMessage(message);
    int i=0;
  //  foreach(QTcpSocket * cliento,clients)
        for (int i=0; i< clients.size(); i++)
    {
QTcpSocket * cliento = clients[i];
        cliento->write(message);
        //cliento->flush();


qDebug() << "sendMessageToAllClients " << i++ << "successfull: " <<  cliento->waitForBytesWritten(time_out_wait);
      /*  if (!cliento->flush())
            rezult = false;
        if (!cliento->waitForBytesWritten(time_out_wait))
            rezult = false;*/
    }
    return rezult;
}


void ServerTCP::clientDisconected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    //qDebug() << "Client disconnected:" << client->peerAddress().toString();
    //clients.remove(client);
    foreach(QTcpSocket *client, clients)
        client->write(QString("Server:  has left.\n").toUtf8());
}

void ServerTCP::readMessage()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    //if (client->)
    QByteArray message = client->readAll();
    emit receivedMessage(message);
}

bool ServerTCP::listenHostPort()
{
    if (!listen(host_adress,port))
        return false;
return true;
    if (!this->waitForNewConnection(time_out_wait))
    {
        this->close();
        return false;
    }
    return true;
}

quint16 ServerTCP::getPort() const
{
    return port;
}

void ServerTCP::setPort(const quint16 &value)
{
    port = value;
}

QHostAddress ServerTCP::getHostAdress() const
{
    return host_adress;
}

void ServerTCP::setHostAdress(const QHostAddress &value)
{
    host_adress = value;
}

