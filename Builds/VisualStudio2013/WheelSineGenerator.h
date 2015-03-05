#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WheelSineGenerator
{
public:
	//==============================================================================
	WheelSineGenerator();
	~WheelSineGenerator();
	void getNextAudioBlock(const AudioSourceChannelInfo&);
	void initWheel();
private:
	//==============================================================================
	double frequency, sampleRate;
	double currentPhase, phasePerSample;
	float amplitude;

};

