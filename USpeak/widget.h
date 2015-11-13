#ifndef WIDGET_H
#define WIDGET_H


#include "includes.h"
#include <server.h>
#include "account.h"
#include "clienttcp.h"
#include "servertcp.h"
#include "audiorecorder.h"
#include "audiodecoder.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    AudioDecoder* decoder;
    AudioRecorder* recorder;

    bool client_or_server;
    Account myself;
    Server *connector;
    ClientTcp* client_tcp;
    ServerTCP* server_tcp;
    bool con_skok = false;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



    Account* getMyself() ;
    void setMyself(const Account &value);
    Server *getConnecor() const;
    void setConnecor(Server *value);

public slots:
    void messageOutput(QString msg);
    void messageOutput(QByteArray msg);

    void audioOutput(QByteArray audio);

    void logOutput(QString log);
    void serverFounded();
    void clientConnected();


    void on_send_button_clicked();

    void on_connect_button_clicked();

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_listen_clicked();

    void on_listen_button_clicked();

    void on_speak_button_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
