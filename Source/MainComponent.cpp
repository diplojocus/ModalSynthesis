/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "AudioCore.h"
#include "TimeView.h"
#include "FrequencyView.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (1000, 400);
	
	theAudioCore = new AudioCore(this, String("/Users/joe/Downloads/footstep.wav"));
	
	theTimeView = new TimeView();
	theTimeView->setBounds(0, 0, getWidth(), getHeight()*0.5f);
	addAndMakeVisible(theTimeView);
	
	theFrequencyView = new FrequencyView();
	theFrequencyView->setBounds(0, getHeight()*0.5f, getWidth(), getHeight()*0.5f);
	addAndMakeVisible(theFrequencyView);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
}

void MainContentComponent::resized()
{
}

void MainContentComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	theTimeView->buffer = theAudioCore->sampleInputBuffer.getSampleData(0);
	theTimeView->numSamples = theAudioCore->sampleInputBuffer.getNumSamples();
	
	theFrequencyView->buffer = theAudioCore->fftOutputBuffer.getSampleData(0);
	theFrequencyView->numSamples = theAudioCore->fftWindowSize;
	theFrequencyView->freqStart = theAudioCore->sampleRate / theAudioCore->fftWindowSize;
	theFrequencyView->freqEnd = theAudioCore->sampleRate * 0.5f;
	theFrequencyView->freqScale = log10f(theFrequencyView->freqEnd/theFrequencyView->freqStart);
	
	repaint();
}
