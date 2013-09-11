/*
  ==============================================================================

    FrequencyView.h
    Created: 11 Sep 2013 11:48:30pm
    Author:  Joe White

  ==============================================================================
*/

#ifndef FREQUENCYVIEW_H_INCLUDED
#define FREQUENCYVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FrequencyView    : public Component
{
public:
    FrequencyView();
    ~FrequencyView();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencyView)
};


#endif  // FREQUENCYVIEW_H_INCLUDED
