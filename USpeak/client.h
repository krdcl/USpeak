#ifndef CLIENT_H
#define CLIENT_H
#include <includes.h>

class Client : public QTcpSocket
{
    QHostAddress host_adress = QHostAddress("192.168.1.132");
    quint16 port = 5765;

    Account myself;
    QSet<Connector *> clients;
public:
    Client();
    ~Client();
};

#endif // CLIENT_H
