#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
                QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        QNetworkSession *networkSession = new QNetworkSession(config, &app);
        networkSession->open();
        networkSession->waitForOpened();

        if (networkSession->isOpen()) {
            // Save the used configuration
            QNetworkConfiguration config = networkSession->configuration();
            QString id;
            if (config.type() == QNetworkConfiguration::UserChoice) {
                id = networkSession->sessionProperty(
                            QLatin1String("UserChoiceConfiguration")).toString();
            } else {
                id = config.identifier();
            }

            QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
            settings.beginGroup(QLatin1String("QtNetwork"));
            settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
            settings.endGroup();
        }
    }

    /*  Widget w;
    w.show();
    w.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);*/

    QWidget w;
    w.show();

    QFile music("E:\\Roxette - Listen To Your Heart  (audiopoisk.com).mp3");
    music.open(QFile::ReadOnly);


    /* QMediaPlayer player;
    QByteArray content = music.readAll();
    QBuffer audio_buffer(&content);

    player.setMedia(QMediaContent(),&audio_buffer);

    // player.setMedia(QUrl::fromLocalFile("E:\\Roxette - Listen To Your Heart  (audiopoisk.com).mp3"));
    player.setVolume(100);
    player.play();
    */

    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
    }
    else
    {
        QAudioOutput * audio = new QAudioOutput(format, &w);
        audio->start(&music);
    }




    /*
    AudioDecoder player;
    player.setNextContent();
    player.play();*/
    /*while (!init)
    {
        w.logOutput(QString("Search someone...   "));

        init = w.getConnecor()->connectOrListen(skok);
        qApp->processEvents(QEventLoop::AllEvents);
        skok = !skok;
    }*/
    return app.exec();
}
