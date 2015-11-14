#include "audiorecorder.h"

AudioRecorder::AudioRecorder(QObject *parent) : QObject(parent)
{

    audio_recorder = new QAudioRecorder(this);
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::LowQuality);

    audio_recorder->setEncodingSettings(audioSettings);

   // audio_recorder->setOutputLocation(QUrl::fromLocalFile("test.amr"));

    audioProbe = new QAudioProbe(this);
    if ( audioProbe->setSource( audio_recorder ))
    {
        // Probing succeeded, audioProbe->isValid() should be true.
        connect(audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)),
                this, SLOT(calculateLevel(QAudioBuffer)));
    }

    timer_out =  new QTimer (this);\
    timer_out->setInterval(15);
    //connect(timer_out,SIGNAL(timeout()),this,SIGNAL(audioBufferder()));
}

AudioRecorder::~AudioRecorder()
{

}

void AudioRecorder::calculateLevel(QAudioBuffer buffer)
{
    QByteArray b_array = (const char*) buffer.constData();
    emit audioBufferder(b_array);
}

void AudioRecorder::beginRecord()
{
    audio_recorder->record();

    timer_out->start();
}

void AudioRecorder::endRecord()
{
    audio_recorder->stop();
}
