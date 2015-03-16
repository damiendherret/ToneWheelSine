#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


class WheelSineGenerator	
{
public:
	//==============================================================================
	WheelSineGenerator(/*ToneWheelSineAudioProcessor&*/);
	~WheelSineGenerator();
	void getNextAudioBlock(const AudioSourceChannelInfo&);
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples, MidiBuffer& midiMessages);
    void handleMidiEvent (const MidiMessage& m);
	void initWheel(double sampleRate, HashMap<String, float*> *,HashMap<String, float*> *,int*);
    void setParameter(String name, float parameterValue);
    
private:
	//==============================================================================
    //ToneWheelSineAudioProcessor& processor;
    float getSineValue(double frequency, double time, double phase);
    float computeNote(int note);
	double sampleRate;
	double currentPhase, phasePerSample;
	float amplitude;
    double attackTimeInMs;
    double releaseTimeInMs;
    juce::HashMap<int, struct WheelNote>notesOn;
    
    float subSlider, slider5, mainSlider, slider8, slider12, slider15, slider17, slider19, slider22;
    float phaseSubSlider, phaseSlider5, phaseMainSlider, phaseSlider8, phaseSlider12, phaseSlider15, phaseSlider17,phaseSlider19, phaseSlider22;
    
    HashMap<String, float*> slidersValues;
    HashMap<String, float*> slidersPhaseValues;
    int* harmonicStyle;
    //juce::Array<struct WheelNote> notesOn;
    

};

