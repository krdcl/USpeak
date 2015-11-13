#ifndef AUDIODECODER_H
#define AUDIODECODER_H

#include "includes.h"

class AudioDecoder : public QObject
{
    Q_OBJECT

     QAudioOutput* audio_output;
     QMediaPlayer *player;
     QBuffer audio_buffer;
public:
     AudioDecoder(QObject *parent = 0);
    ~AudioDecoder();

    void play();
    void stop();
    void setNextContent(QByteArray content);
    void playNextContent();
};

#endif // AUDIODECODER_H
