#include "WheelSineGenerator.h"


WheelSineGenerator::WheelSineGenerator()
{
}


WheelSineGenerator::~WheelSineGenerator()
{
}

void WheelSineGenerator::initWheel()
{
	double waveforms[3];
	frequency = 440;
	sampleRate = 44100;
	currentPhase = 0;
	phasePerSample = 0.0;
	amplitude = 0.8f;
}

// DEPRECATED ================================================================
void WheelSineGenerator::getNextAudioBlock(const AudioSourceChannelInfo& info)
{
	if (phasePerSample == 0.0)
		phasePerSample = (double_Pi * 2.0 * frequency) / sampleRate;
	//phasePerSample = double_Pi * 2.0 / (sampleRate / frequency);


	for (int i = 0; i < info.numSamples; ++i)
	{
		const float sample = amplitude * (float)std::sin(currentPhase);
		currentPhase += phasePerSample;
		if (currentPhase > 2.0 * double_Pi)
		{
			currentPhase = currentPhase - (2.0 * double_Pi);
		}
		//Logger::writeToLog("currentPhase :" + std::to_string(currentPhase));

		for (int j = info.buffer->getNumChannels(); --j >= 0;)
			info.buffer->setSample(j, info.startSample + i, sample);
	}
}


void WheelSineGenerator::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
	if (phasePerSample == 0.0)
		phasePerSample = (double_Pi * 2.0 * frequency) / sampleRate;
	for (int i = 0; i < numSamples; ++i)
	{
		const float sample = amplitude * (float)std::sin(currentPhase);
		currentPhase += phasePerSample;
		if (currentPhase > 2.0 * double_Pi)
		{
			currentPhase = currentPhase - (2.0 * double_Pi);
		}
		//Logger::writeToLog("currentPhase :" + std::to_string(currentPhase));

		for (int j = outputBuffer.getNumChannels(); --j >= 0;)
			outputBuffer.addSample(j, startSample, sample);
		++startSample;
	}
	
}