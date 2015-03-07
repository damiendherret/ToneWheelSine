#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WheelSineGenerator	
{
public:
	//==============================================================================
	WheelSineGenerator();
	~WheelSineGenerator();
	void getNextAudioBlock(const AudioSourceChannelInfo&);
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples, MidiBuffer& midiMessages);
    void handleMidiEvent (const MidiMessage& m);
	void initWheel(double sampleRate);
    
private:
	//==============================================================================
    float getSineValue(double frequency, double time, double phase);
	double frequency, sampleRate;
	double currentPhase, phasePerSample;
	float amplitude;
    int attackTimeInMs;
    int releaseTimeInMs;
    juce::HashMap<int, struct WheelNote>notesOn;
    //juce::Array<struct WheelNote> notesOn;
    

};

