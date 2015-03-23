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
class ToneWheelSineAudioProcessorEditor  : public AudioProcessorEditor,
                                            private Slider::Listener
{
public:
    ToneWheelSineAudioProcessorEditor (ToneWheelSineAudioProcessor&);
    ~ToneWheelSineAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void initSlider(Slider &slider, int position);
    void initPhaseSlider(Slider &slider, int position);
    void initWaveSlider(Slider &slider, int position);
    void initTremSlider(Slider &slider, int position);
    void reloadValues();
    void sliderValueChanged (Slider* slider) override;



private:    
    
    ToneWheelSineAudioProcessor& processor;
    
    //Bar sliders ==============
    Slider subSlider, slider5, mainSlider, slider8, slider12, slider15, slider17, slider19, slider22;
    Array<Slider*> sliders;
    Array<juce::String> sliderNames = {"subSlider", "slider5", "mainSlider", "slider8", "slider12", "slider15", "slider17", "slider19", "slider22"};
    
    //Phase sliders ==============
    Slider subPhaseSlider, phaseSlider5, mainPhaseSlider, phaseSlider8, phaseSlider12, phaseSlider15, phaseSlider17, phaseSlider19, phaseSlider22;
    Array<Slider*> phaseSliders;
    Array<juce::String> phaseSliderNames = {"phaseSubSlider", "phaseSlider5", "phaseMainSlider", "phaseSlider8", "phaseSlider12", "phaseSlider15", "phaseSlider17", "phaseSlider19", "phaseSlider22"};
    
    //Wave sliders ==============
    Slider subWaveSlider, waveSlider5, mainWaveSlider, waveSlider8, waveSlider12, waveSlider15, waveSlider17, waveSlider19, waveSlider22;
    Array<Slider*> waveSliders;
    Array<juce::String> waveSliderNames = {"waveSubSlider", "waveSlider5", "waveMainSlider", "waveSlider8", "waveSlider12", "waveSlider15", "waveSlider17", "waveSlider19", "waveSlider22"};
    
    //Tremolo sliders ==============
    Slider subTremSlider, tremSlider5, mainTremSlider, tremSlider8, tremSlider12, tremSlider15, tremSlider17, tremSlider19, tremSlider22;
    Array<Slider*> tremSliders;
    Array<juce::String> tremSliderNames = {"tremSubSlider", "tremSlider5", "tremMainSlider", "tremSlider8", "tremSlider12", "tremSlider15", "tremSlider17", "tremSlider19", "tremSlider22"};
    
    
    //Other controls
    Slider volumeSlider;
    Slider harmonicStyle;
    Slider tremoloSpeedSlider;
    Slider tremoloDepthSlider;
    
    //Reload Management
    //bool valuesSet = false;

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToneWheelSineAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
