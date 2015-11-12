#include "widget.h"
#include "ui_widget.h"


Server *Widget::getConnecor() const
{
    return connector;
}

void Widget::setConnecor(Server *value)
{
    connector = value;
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connector = new Server(this);

    myself.setName(QString("user ") + QString::number(qrand()));

    connect(connector,SIGNAL(massageReceived(QByteArray)),this,SLOT(messageOutput(QByteArray)));

    connect(connector,SIGNAL(logInfoSignal(QString)),this,SLOT(messageOutput(QString)));


    ui->message_output->setReadOnly(true);
    ui->text_log->setReadOnly(true);


    QString host_rand = QString::number(rand() * 255) + QString(".") +
            QString::number(rand() * 255) + QString(".") +
            QString::number(rand() * 255) + QString(".") +
            QString::number(rand() * 255);
    // QHostAddress host = QHostAddress(host_rand);
   // QHostAddress host =  QHostAddress::LocalHost ;;
    QHostAddress host =  QHostAddress::Broadcast;
    connector->setPort(qrand());
    connector->setHostAdress(host);
   // connector->bindHostPort();

   // connector->joinMulticastGroup(host);

    client_tcp = new ClientTcp(this);
    server_tcp = new ServerTCP(this);
    connect(client_tcp,SIGNAL(sendedMessage(QByteArray)),this,SLOT(messageOutput(QByteArray)));
    connect(client_tcp,SIGNAL(receivedMessage(QByteArray)),this,SLOT(messageOutput(QByteArray)));

    //connect(server_tcp,SIGNAL(),this,SLOT());
    connect(client_tcp,SIGNAL(sendedMessage(QByteArray)),this,SLOT(messageOutput(QByteArray)));
    connect(client_tcp,SIGNAL(receivedMessage(QByteArray)),this,SLOT(messageOutput(QByteArray)));


    //    connecor->ho
}

Widget::~Widget()
{
    delete ui;
    delete connector;
    delete client_tcp;
    delete server_tcp;
}


void Widget::messageOutput(QString msg)
{
    this->ui->message_output->append(msg);

}

void Widget::messageOutput(QByteArray msg)
{
    this->ui->message_output->append(QString(msg));

}

void Widget::logOutput(QString log)
{
    this->ui->text_log->append(log +  QString( " ") + QTime::currentTime().toString() + QString( " ") + QDate::currentDate().toString());
}

Account* Widget::getMyself()
{
    return &myself;
}

void Widget::setMyself(const Account &value)
{
    myself = value;
}



void Widget::on_send_button_clicked()
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

    // connecor->bind(QHostAddress::LocalHost, connecor->getPort());
    connector->sendMessage(message.toLocal8Bit());
}

void Widget::on_connect_button_clicked()
{
    //logOutput(QString("Search clients...   "));


}

void Widget::on_pushButton_connect_clicked()
{

    while (true)
    {
        logOutput(QString("Search clients...   "));
        if ( client_tcp->connectToHostPort() )
        {
            client_or_server = false;
            break;
        }
        /*if ( server_tcp )
        {
            client_or_server = false;
            break;
        }*/
    }

    client_or_server = true;
    // connector->joinMulticastGroup(connector->getHostAdress());
}

void Widget::on_pushButton_listen_clicked()
{
    // logOutput(QString("Search server...   "));
    //connecor->connectOrListen(false);
}
