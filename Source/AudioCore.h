/*
  ==============================================================================

    AudioCore.h
    Created: 9 Sep 2013 10:00:07pm
    Author:  Joe White

  ==============================================================================
*/

#ifndef AUDIOCORE_H_INCLUDED
#define AUDIOCORE_H_INCLUDED

#include "JuceHeader.h"

class AudioCore: public ChangeBroadcaster
{
public:
	AudioCore(ChangeListener *listener, const String &filePath);
	~AudioCore();
	
	float sampleRate;
	uint64 fftWindowSize;
	AudioSampleBuffer sampleInputBuffer;
	AudioSampleBuffer fftOutputBuffer;
private:
};

#endif  // AUDIOCORE_H_INCLUDED
