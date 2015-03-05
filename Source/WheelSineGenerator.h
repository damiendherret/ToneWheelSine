#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WheelSineGenerator
{
public:
	//==============================================================================
	WheelSineGenerator();
	~WheelSineGenerator();
	void getNextAudioBlock(const AudioSourceChannelInfo&);
	void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples);
	void initWheel();
private:
	//==============================================================================
	double frequency, sampleRate;
	double currentPhase, phasePerSample;
	float amplitude;

};

