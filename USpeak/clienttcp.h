#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <includes.h>

class ClientTcp : public QTcpSocket
{
    Q_OBJECT

    QHostAddress host_adress;
    quint16 port ;
     int time_out_wait;
public:
    explicit ClientTcp(QObject *parent = 0);
    ~ClientTcp();

       void doConnect();
       bool connectToHostPort();
       quint16 getPort() const;
       void setPort(const quint16 &value);
       QHostAddress getHostAdress() const;
       void setHostAdress(const QHostAddress &value);

       bool writeMessage(QByteArray message);
public slots:
       void readMessage();

signals:
       void receivedMessage(QByteArray msg);
       void sendedMessage(QByteArray msg);
};

#endif // CLIENTTCP_H
