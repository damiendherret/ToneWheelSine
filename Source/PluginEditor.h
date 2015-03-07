/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class ToneWheelSineAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ToneWheelSineAudioProcessorEditor (ToneWheelSineAudioProcessor&);
    ~ToneWheelSineAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void initSlider(Slider &slider, int position);

private:
    
    
    ToneWheelSineAudioProcessor& processor;
    
    Slider subSlider, slider5, mainSlider, slider8, slider12, slider15, slider17,slider19, slider22;
    
    Array<Slider*> sliders;

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToneWheelSineAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
