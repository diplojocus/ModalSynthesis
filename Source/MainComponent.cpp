/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "AudioCore.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (1000, 400);
	
	theAudioCore = new AudioCore(this, String("/Users/joe/Downloads/footstep.wav"));

	float freqStart = theAudioCore->sampleRate / theAudioCore->bufferSize;
	float freqEnd = theAudioCore->sampleRate * 0.5f;
	scale = log10f(freqEnd/freqStart);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
	Path fftPath = Path();
	fftPath.startNewSubPath(0, getHeight());
	
	float *samples = theAudioCore->buffer.getSampleData(0);
	int numSamples = theAudioCore->bufferSize/2;
	
	float freqStart = theAudioCore->sampleRate / theAudioCore->bufferSize;
	
	for (int i = 1; i < numSamples; i++)
	{
		float binFrequency = freqStart * i;
		float xScale = log10f(binFrequency/freqStart) / scale;
		float sample = samples[i];
		fftPath.lineTo(getWidth()*xScale, getHeight()-sample*getHeight());
	}
	g.strokePath(fftPath, PathStrokeType(2.0f));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	repaint();
}
