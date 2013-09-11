/*
  ==============================================================================

    TimeView.h
    Created: 11 Sep 2013 11:48:10pm
    Author:  Joe White

  ==============================================================================
*/

#ifndef TIMEVIEW_H_INCLUDED
#define TIMEVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TimeView    : public Component
{
public:
    TimeView();
    ~TimeView();

    void paint (Graphics&);
    void resized();
	
	float *buffer;
	int numSamples;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeView)
};


#endif  // TIMEVIEW_H_INCLUDED
