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
	sampleRate(44100.0f),
	fftWindowSize(8192),
	sampleInputBuffer(AudioSampleBuffer(1, 0)),
	fftOutputBuffer(AudioSampleBuffer(1, 0))
{
	addChangeListener(listener);
	
	File audioFile(filePath);
	AudioFormatManager formatManager;
	formatManager.registerBasicFormats();
	ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(audioFile);
	
	if (reader != nullptr)
	{
		sampleRate = (float)reader->sampleRate;
		fftOutputBuffer = AudioSampleBuffer(1, fftWindowSize);

		sampleInputBuffer = AudioSampleBuffer(reader->numChannels, reader->lengthInSamples);
		reader->read(&sampleInputBuffer, 0, reader->lengthInSamples, 0, true, true);
		
		kiss_fftr_cfg cfg;
		if ((cfg = kiss_fftr_alloc(fftWindowSize, 0, NULL, NULL)) != NULL)
		{
			float *inputBuffer = sampleInputBuffer.getSampleData(0);
			float *fftBuffer = fftOutputBuffer.getSampleData(0);
			kiss_fft_cpx complexBuffer[(fftWindowSize/2)+1];
			for (int i = 0; i < fftWindowSize; i++)
			{
				float hanningCoeff = 0.5 * (1 - cosf(2*M_PI*i/(fftWindowSize-1)));
				fftBuffer[i] = inputBuffer[i];
				fftBuffer[i] *= hanningCoeff;
			}
			kiss_fftr(cfg, fftBuffer, complexBuffer);
			for (int i = 0; i < fftWindowSize/2+1; i++)
			{
				fftBuffer[i] = sqrtf((complexBuffer[i].r * complexBuffer[i].r) + (complexBuffer[i].i * complexBuffer[i].i));
				fftBuffer[i] /= sqrtf(fftWindowSize);
			}
			fftBuffer[0] = 0.0f; // [0] = DC Offset
		}
		sendChangeMessage();
	}
}

AudioCore::~AudioCore()
{
}
