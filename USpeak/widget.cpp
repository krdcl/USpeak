#include "widget.h"
#include "ui_widget.h"


Server *Widget::getConnecor() const
{
    return connecor;
}

void Widget::setConnecor(Server *value)
{
    connecor = value;
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connecor = new Server(this);

    myself.setName(QString("user ") + QString::number(qrand()));

    connect(connecor,SIGNAL(massageReceived(QByteArray)),this,SLOT(messageOutput(QByteArray)));

    connect(connecor,SIGNAL(logInfoSignal(QString)),this,SLOT(messageOutput(QString)));


    ui->message_output->setReadOnly(true);
    ui->text_log->setReadOnly(true);

   // connecor->setPort(qrand());
}

Widget::~Widget()
{
    delete ui;
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
   connecor->sendMessage(message.toLocal8Bit());
}

void Widget::on_connect_button_clicked()
{
     logOutput(QString("Search clients...   "));

   connecor->bind(QHostAddress::LocalHost, connecor->getPort());
}

void Widget::on_pushButton_connect_clicked()
{
    logOutput(QString("Search clients...   "));
   connecor->bind(QHostAddress::LocalHost, connecor->getPort());
}

void Widget::on_pushButton_listen_clicked()
{
   // logOutput(QString("Search server...   "));
    //connecor->connectOrListen(false);
}
