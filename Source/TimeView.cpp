/*
  ==============================================================================

    TimeView.cpp
    Created: 11 Sep 2013 11:48:10pm
    Author:  Joe White

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TimeView.h"

//==============================================================================
TimeView::TimeView()
{
	numSamples = 0;
	buffer = NULL;
}

TimeView::~TimeView()
{
	buffer = NULL;
}

void TimeView::paint (Graphics& g)
{
	g.fillAll (Colours::white);
	if (buffer != NULL)
	{
		g.setColour(Colours::blue);
		for (int i = 0; i < getWidth(); i++)
		{
			int index = ((float)i / (float)getWidth()) * numSamples;
			float sample = buffer[index];
			sample += 1.0f;
			sample *= 0.5f;
			g.drawLine((float)i, sample*getHeight(), (float)i, getHeight()-sample*getHeight());
		}
	}
}

void TimeView::resized()
{
}

