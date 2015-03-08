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
    
private:
	//==============================================================================
    //ToneWheelSineAudioProcessor& processor;
    float getSineValue(double frequency, double time, double phase);
    float computeNote(int note);
	double frequency, sampleRate;
	double currentPhase, phasePerSample;
	float amplitude;
    double attackTimeInMs;
    double releaseTimeInMs;
    juce::HashMap<int, struct WheelNote>notesOn;
    HashMap<String, float*> slidersValues;
    HashMap<String, float*> slidersPhaseValues;
    int* harmonicStyle;
    //juce::Array<struct WheelNote> notesOn;
    

};

