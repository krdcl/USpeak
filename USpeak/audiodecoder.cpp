#include "audiodecoder.h"

AudioDecoder::AudioDecoder(QObject *parent) : QObject(parent)
{
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
        return;
    }

    audio_output = new QAudioOutput(format, this);

    player = new QMediaPlayer(this);
    //connect(player,SIGNAL())
}

AudioDecoder::~AudioDecoder()
{

}

void AudioDecoder::play()
{
    player->play();
}

void AudioDecoder::stop()
{
    player->stop();
}

void AudioDecoder::setNextContent(QByteArray content)
{
    audio_buffer.setBuffer(&content);
}

void AudioDecoder::playNextContent()
{
    player->setMedia(QMediaContent(), &audio_buffer);
    player->play();
}


