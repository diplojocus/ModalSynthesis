/*
  ==============================================================================

    AudioCore.cpp
    Created: 9 Sep 2013 10:00:07pm
    Author:  Joe White

  ==============================================================================
*/

#include "AudioCore.h"
#include "kiss_fft.h"

AudioCore::AudioCore(ChangeListener *listener, const String &filePath):
	buffer(AudioSampleBuffer(1, 0))
{
	addChangeListener(listener);

	bufferSize = 128;
	
	File audioFile(filePath);
	AudioFormatManager formatManager;
	formatManager.registerBasicFormats();
	ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(audioFile);
	if (reader != nullptr)
	{
		buffer = AudioSampleBuffer(reader->numChannels, bufferSize);
		reader->read(&buffer, 0, bufferSize, 0, true, true);
		
		kiss_fft_cfg cfg;
		if ((cfg = kiss_fft_alloc(bufferSize, 1, NULL, NULL)) != NULL)
		{
			float *sampleBuffer = buffer.getSampleData(0);
			kiss_fft_cpx inputBuffer[bufferSize];
			kiss_fft_cpx outputBuffer[(bufferSize/2)+1];
			for (int i = 0; i < bufferSize; i++)
			{
				float hanningCoeff = 0.5 * (1 - cosf(2*M_PI*i/(bufferSize-1)));
				inputBuffer[i].r = sampleBuffer[i] * hanningCoeff;
				inputBuffer[i].i = 0;
			}
			kiss_fft(cfg, inputBuffer, outputBuffer);
			
			for (int i = 0; i < bufferSize/2; i++)
			{
				sampleBuffer[i] = sqrtf((outputBuffer[i].r * outputBuffer[i].r) + (outputBuffer[i].i * outputBuffer[i].i));
				printf("%f\n", *(sampleBuffer+i));
			}
			printf("\n");
		}
		sendChangeMessage();
	}
}

AudioCore::~AudioCore()
{
}
