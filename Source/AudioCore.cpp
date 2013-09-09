/*
  ==============================================================================

    AudioCore.cpp
    Created: 9 Sep 2013 10:00:07pm
    Author:  Joe White

  ==============================================================================
*/

#include "AudioCore.h"

AudioCore::AudioCore(ChangeListener *listener, const String &filePath):
	buffer(AudioSampleBuffer(1, 0))
{
	addChangeListener(listener);

	bufferSize = 2048;
	
	File audioFile(filePath);
	AudioFormatManager formatManager;
	formatManager.registerBasicFormats();
	ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(audioFile);
	if (reader != nullptr)
	{
		buffer = AudioSampleBuffer(reader->numChannels, bufferSize);
		reader->read(&buffer, 0, bufferSize, 0, true, true);
		sendChangeMessage();
	}
}

AudioCore::~AudioCore()
{
}
