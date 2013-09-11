/*
  ==============================================================================

    AudioCore.cpp
    Created: 9 Sep 2013 10:00:07pm
    Author:  Joe White

  ==============================================================================
*/

#include "AudioCore.h"
#include "kiss_fftr.h"

AudioCore::AudioCore(ChangeListener *listener, const String &filePath):
	buffer(AudioSampleBuffer(1, 0))
{
	addChangeListener(listener);
	sampleRate = 44100.0f;
	bufferSize = 8192;
	
	File audioFile(filePath);
	AudioFormatManager formatManager;
	formatManager.registerBasicFormats();
	ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(audioFile);
	if (reader != nullptr)
	{
		buffer = AudioSampleBuffer(reader->numChannels, bufferSize);
		reader->read(&buffer, 0, bufferSize, 0, true, true);
		
		kiss_fftr_cfg cfg;
		if ((cfg = kiss_fftr_alloc(bufferSize, 0, NULL, NULL)) != NULL)
		{
			float *sampleBuffer = buffer.getSampleData(0);
			kiss_fft_cpx outputBuffer[(bufferSize/2)+1];
			for (int i = 0; i < bufferSize; i++)
			{
				float hanningCoeff = 0.5 * (1 - cosf(2*M_PI*i/(bufferSize-1)));
				sampleBuffer[i] *= hanningCoeff;
			}
			kiss_fftr(cfg, sampleBuffer, outputBuffer);
			for (int i = 0; i < bufferSize/2+1; i++)
			{
				sampleBuffer[i] = sqrtf((outputBuffer[i].r * outputBuffer[i].r) + (outputBuffer[i].i * outputBuffer[i].i));
				sampleBuffer[i] /= sqrtf(bufferSize);
			}
			sampleBuffer[0] = 0.0f; // [0] = DC Offset
		}
		sendChangeMessage();
	}
}

AudioCore::~AudioCore()
{
}
