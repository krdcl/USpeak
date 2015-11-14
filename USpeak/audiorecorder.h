#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include "includes.h"

class AudioRecorder: public QObject
{
    Q_OBJECT

    QAudioRecorder * audio_recorder;
    QAudioProbe* audioProbe;
    QTimer *timer_out;

public:

    AudioRecorder(QObject *parent = 0);
    ~AudioRecorder();
    void beginRecord();
    void endRecord();
signals:
    void audioBufferder(QByteArray buffer);
    void audioBufferder();

public slots:
    void calculateLevel(QAudioBuffer buffer);

};

#endif // AUDIORECORDER_H
