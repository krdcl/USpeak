#ifndef CONNECTOR_H
#define CONNECTOR_H


class Connector: public QTcpServer, QTcpSocket
{
    Q_OBJECT
    QHostAddress host_adress = QHostAddress("192.168.1.132");
    quint16 port = 5765;

    Account myself;
    QSet<Connector *> clients;
public:
    explicit Connector(QObject *parent = Q_NULLPTR);
    ~Connector();
    quint16 getPort() const;
    void setPort(const quint16 &value);
    int getClientCount();
    void sendMessage(QString message);
    Account* getMyself() const;
    void setMyself(const Account &value);

    void reConnection();

    QHostAddress getHost();
    void setHost(QHostAddress address);
    bool searchConnections(int time);
signals:

    void receivedMessageSignal(QString msg);
    void logInfoSignal(QString info);
public slots:
    void readMessageSlot();
    void addConnection();
    void readyRead();
    void disconnectedSlot();


};

#endif // CONNECTOR_H
