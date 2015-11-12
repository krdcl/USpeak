#ifndef SERVERTCP_H
#define SERVERTCP_H

#include "includes.h"

class ServerTCP : public QTcpServer
{
    Q_OBJECT

    QHostAddress host_adress;
    quint16 port ;
   QList <QTcpSocket *> clients;
   int time_out_wait;
public:
    explicit  ServerTCP(QObject *parent = 0);
    ~ServerTCP();

   bool sendMessageToAllClients(QByteArray message);
   bool listenHostPort();

   void setPort(const quint16 &value);
   QHostAddress getHostAdress() const;
   void setHostAdress(const QHostAddress &value);

   quint16 getPort() const;


public slots:
    void newClient();
    void readMessage();
    void clientDisconected();
signals:

       void sendedMessage(QByteArray msg);
        void receivedMessage(QByteArray msg);
};

#endif // SERVERTCP_H
