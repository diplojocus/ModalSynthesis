/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioCore;
class TimeView;
class FrequencyView;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, ChangeListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();
	
    void paint (Graphics&);
    void resized();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
	
	float scale;
	
	ScopedPointer<AudioCore> theAudioCore;
	ScopedPointer<TimeView> theTimeView;
	ScopedPointer<FrequencyView> theFrequencyView;
	
	void changeListenerCallback(ChangeBroadcaster* source);
};


#endif  // MAINCOMPONENT_H_INCLUDED
