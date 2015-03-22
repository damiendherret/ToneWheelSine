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
	void initWheel(double sampleRate, HashMap<String, float*> *, HashMap<String, float*> *, HashMap<String, int*> *, HashMap<String, float*> *, int*, float*, float*);
    void setParameter(String name, float parameterValue);
    void debugParameters();
    
private:
	//==============================================================================
    //ToneWheelSineAudioProcessor& processor;
    float getValue(double frequency, double time, double phase,int waveform);
    float getSineValue(double frequency, double time, double phase);
    float getTriangleValue(double frequency, double time, double phase);
    float getTremoloGain(double time);
    float computeNote(int note);
	double sampleRate;
	double currentPhase, phasePerSample;
	float amplitude;
    double attackTimeInMs;
    double releaseTimeInMs;
    double gainOn = 1.01;
    double gainOff = 0.99;
    float tremBaseFrequency;
    
    juce::HashMap<int, struct WheelNote>notesOn;
    
    float subSlider, slider5, mainSlider, slider8, slider12, slider15, slider17, slider19, slider22;
    float phaseSubSlider, phaseSlider5, phaseMainSlider, phaseSlider8, phaseSlider12, phaseSlider15, phaseSlider17,phaseSlider19, phaseSlider22;
    int waveSubSlider, waveSlider5, waveMainSlider, waveSlider8, waveSlider12, waveSlider15, waveSlider17, waveSlider19, waveSlider22;
    float tremSubSlider, tremSlider5, tremMainSlider, tremSlider8, tremSlider12, tremSlider15, tremSlider17, tremSlider19, tremSlider22;
    
    HashMap<String, float*> slidersValues;
    HashMap<String, float*> slidersPhaseValues;
    HashMap<String, int*> slidersWaveValues;
    HashMap<String, float*> slidersTremValues;
    int* harmonicStyle;
    float* tremoloSpeed;
    float* tremoloDepth;
    //juce::Array<struct WheelNote> notesOn;
    
    bool ready = false;
    

};

