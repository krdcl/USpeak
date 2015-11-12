#ifndef WIDGET_H
#define WIDGET_H


#include "includes.h"
#include <server.h>
#include "account.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT


    Account myself;
    Server *connector;
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
    void logOutput(QString log);

public slots:
    void on_send_button_clicked();

    void on_connect_button_clicked();

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_listen_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
