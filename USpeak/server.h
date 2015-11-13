#ifndef SERVER_H
#define SERVER_H
#include <includes.h>

class Server: public QUdpSocket
{
    Q_OBJECT
    QHostAddress host_adress = QHostAddress("192.168.1.132");
    quint16 port = 5765;

    int time_out = 2000;
    QTcpSocket* my_client;
    QSet<QTcpSocket *> clients;
    bool server_or_client = false;
public:
    Server(QObject *parent = Q_NULLPTR);
     ~Server();

    void setHostAdress(QHostAddress adress);
    void setHostAdress(QString adress);
    QHostAddress getHostAdress();
    void bindHostPort();



    quint16 getPort() const;
    void setPort(const quint16 &value);

signals:
    void massageReceived(QByteArray msg);
    void massageSended(QByteArray msg);
public slots:
    void readPendingDatagrams();
     void sendMessage(QByteArray datagram);

};

#endif // SERVER_H
