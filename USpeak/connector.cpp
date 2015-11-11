#include "connector.h"




quint16 Connector::getPort() const
{
    return port;
}

void Connector::setPort(const quint16 &value)
{
    port = value;
}

Account* Connector::getMyself() const
{
    return &myself;
}

void Connector::setMyself(const Account &value)
{
    myself = value;
}
Connector::Connector( QObject *parent)
{
    this->setParent(parent);
    host_adress = QHostAddress("127.0.0.1");

    // whenever a user connects, it will emit signal
    connect(this, SIGNAL(newConnection()),
            this, SLOT(addConnection()));

    if(!this->listen(QHostAddress::Any, port))
    {
        emit logInfoSignal (QString("Server could not start server: ") + client->peerAddress().toString());
    }
    else
    {
        emit logInfoSignal (QString("Server started: ") + client->peerAddress().toString());
    }
}

Connector::~Connector()
{

}

QHostAddress Connector::getHost()
{
    return host_adress;
}

void Connector::setHost(QHostAddress address)
{
    host_adress = address;
}

void Connector::addConnection()
{
    Connector *client = new Connector(this);

    emit logInfoSignal (QString("New client from: ") + client->peerAddress().toString());

    connect(client, SIGNAL(readyRead()), this, SLOT(readMessageSlot()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

    clients.push_back(client);

    this->connectToHost(client->getHost(),client->getPort());
}

void Connector::sendMessage(QString message)
{
    foreach(QTcpSocket *client, clients)
    {
        client->write(message);
        //if (client->flush())
    }
}


void Connector::readMessageSlot()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    QByteArray inputArray = client->readAll();
    QString input_from_server(inputArray);

    emit receivedMessageSignal(input_from_server);
}

bool Connector::searchConnections(int time)
{
    this->waitForConnected(time);
}


void Connector::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    emit logInfoSignal (QString("Client disconnected: ") + client->peerAddress().toString() + QString( " ") +
                        QTime::currentTime().toString() + QString( " ") + QDate::currentDate().toString());

    clients.remove(client);

    /* foreach(QTcpSocket *client, clients)
    {
        QString message = "\nFrom: ";
        message += myself.getName();
        message += "\nWhen: ";
        message += QTime::currentTime().toString();
        message += " ";
        message += QDate::currentDate().toString();
        message += "\nText:\n";
        message += (this->ui->message_input->toPlainText());
        messageOutput(message);
        this->ui->message_input->setPlainText("");
         this->ui->message_input->setFocus();
        connecor->sendTextMessage(message);
        client->write(QString("Server:" + user + " has left.\n").toUtf8());
    }*/
}


int Connector::getClientCount()
{
    return clients.size();
}




