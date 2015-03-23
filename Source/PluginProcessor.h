/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "WheelSineGenerator.h"
#include "../JuceLibraryCode/JuceHeader.h"




//==============================================================================
/**
*/
class ToneWheelSineAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ToneWheelSineAudioProcessor();
    ~ToneWheelSineAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;
    void notifyChangedParameter(String sliderName, float value);

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	MidiKeyboardState keyboardState;
    float subSliderValue, slider5Value, mainSliderValue, slider8Value, slider12Value, slider15Value, slider17Value, slider19Value, slider22Value;
    HashMap<String, float*> slidersValues;
    
    float subSliderPhaseValue, slider5PhaseValue, mainSliderPhaseValue, slider8PhaseValue, slider12PhaseValue, slider15PhaseValue, slider17PhaseValue, slider19PhaseValue, slider22PhaseValue;
    HashMap<String, float*> slidersPhaseValues;
    
    int subSliderWaveValue, slider5WaveValue, mainSliderWaveValue, slider8WaveValue, slider12WaveValue, slider15WaveValue, slider17WaveValue, slider19WaveValue, slider22WaveValue;
    HashMap<String, int*> slidersWaveValues;
    
    float subSliderTremValue, slider5TremValue, mainSliderTremValue, slider8TremValue, slider12TremValue, slider15TremValue, slider17TremValue, slider19TremValue, slider22TremValue;
    HashMap<String, float*> slidersTremValues;
    
    float mainVolume;
    int harmonicStyle;
    float tremoloSpeed;
    float tremoloDepth;
    
	//bool isValuesLoaded = false;
    bool isInitialState = true;

private:
    //==============================================================================
    WheelSineGenerator* theWheelGenerator;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToneWheelSineAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
