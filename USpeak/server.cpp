#include "server.h"


quint16 Server::getPort() const
{
    return port;
}

void Server::setPort(const quint16 &value)
{
    port = value;
}
Server::Server( QObject *parent)
{
    // bind(QHostAddress::LocalHost, 7755);
    
    connect(this,SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));

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
      //  if (port != senderPort)
            emit massageReceived(datagram);
    }
}

void Server::bindHostPort()
{
   // bind(host_adress, port);
    bind(45454, QUdpSocket::ShareAddress);
}

void Server::sendMessage(QByteArray datagram)
{
    /* QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    out << this->toPlainText().right(1);*/
    //writeDatagram(datagram, host_adress, port);

    writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress("255.255.255.255"), 45454);
    qDebug() << "writeDatagram";
    emit  massageSended(datagram);
}

void Server::setHostAdress(QHostAddress adress)
{
    host_adress = adress;
}

void Server::setHostAdress(QString adress)
{
    host_adress = QHostAddress(adress);
}

QHostAddress Server::getHostAdress()
{
    return host_adress;
}



