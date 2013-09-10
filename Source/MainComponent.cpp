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
	
	theAudioCore = new AudioCore(this, String("/Users/joe/Desktop/Hadopelagic.wav"));
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
	int numSamples = theAudioCore->bufferSize/2+1;
	
	for (int i = 0; i < numSamples; i++)
	{
		float sample = samples[i];
		float startX = ((float)i / (float)numSamples) * getWidth();
		fftPath.lineTo(startX, getHeight()-sample*getHeight());
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
