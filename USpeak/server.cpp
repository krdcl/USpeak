#include "server.h"

Server::Server( QObject *parent)
{
   // bind(QHostAddress::LocalHost, 7755);

    //connect(SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));

}

Server::~Server()
{

}

void Server::readPendingDatagrams()
{
    while (hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        readDatagram(datagram.data(), datagram.size(),
                     &sender, &senderPort);


       // processTheDatagram(datagram);
        emit massageReceived(datagram);
    }
}

void Server::sendMessage(QByteArray datagram)
{
   /* QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    out << this->toPlainText().right(1);*/
    writeDatagram(datagram, QHostAddress::LocalHost, 2525);
    emit  massageSended(datagram);
}




