#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    /*while (!init)
    {
        w.logOutput(QString("Search someone...   "));

        init = w.getConnecor()->connectOrListen(skok);
        qApp->processEvents(QEventLoop::AllEvents);
        skok = !skok;
    }*/
    return a.exec();
}
