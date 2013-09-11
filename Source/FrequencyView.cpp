/*
  ==============================================================================

    FrequencyView.cpp
    Created: 11 Sep 2013 11:48:30pm
    Author:  Joe White

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FrequencyView.h"

//==============================================================================
FrequencyView::FrequencyView()
{
	numSamples = 0;
	buffer = NULL;
}

FrequencyView::~FrequencyView()
{
	buffer = NULL;
}

void FrequencyView::paint (Graphics& g)
{
    g.fillAll (Colours::lightblue);
	Path fftPath = Path();
	fftPath.startNewSubPath(0, getHeight());
	for (int i = 1; i < numSamples; i++)
	{
		float binFrequency = freqStart * i;
		float xScale = log10f(binFrequency/freqStart) / freqScale;
		float sample = buffer[i];
		fftPath.lineTo(getWidth()*xScale, getHeight()-sample*getHeight());
	}
	g.strokePath(fftPath, PathStrokeType(2.0f));
}

void FrequencyView::resized()
{
}
