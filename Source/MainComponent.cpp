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
	theSampleArray = Array<float>();
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
	for (int i = 0; i < getWidth(); i++)
	{
		int sampleIndex = ((float)i / (float)getWidth()) * theAudioCore->bufferSize;
		float sample = theSampleArray[sampleIndex];
		sample += 1.0f;
		sample *= 0.5f;
		g.drawLine((float)i, sample*getHeight(), (float)i, getHeight()-sample*getHeight());
	}
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	theSampleArray = Array<float>(theAudioCore->buffer.getSampleData(0));
	repaint();
}
