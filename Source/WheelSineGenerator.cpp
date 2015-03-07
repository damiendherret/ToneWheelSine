#include "WheelSineGenerator.h"

struct WheelNote
{
    int note;
    bool attacking;
    bool releasing;
    int64 noteOnTime;
    int64 noteOffTime;
    
};

WheelSineGenerator::WheelSineGenerator()
{
}


WheelSineGenerator::~WheelSineGenerator()
{
}

void WheelSineGenerator::initWheel(double initialSampleRate)
{
	double waveforms[3];
	frequency = 440;
	//sampleRate = 44100;
    sampleRate = initialSampleRate;
	currentPhase = 0;
	phasePerSample = 0.0;
	amplitude = 0.8f;
    
    attackTimeInMs = 3000;
    releaseTimeInMs = 3000;
}



void WheelSineGenerator::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples, MidiBuffer& midiMessages)
{
    //handle midi messages
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        handleMidiEvent(m);
    }
    
    //generate sines and mix

    for (int i = 0; i < numSamples; ++i)
    {
        float sample = 0;
        int64 now = Time::getCurrentTime().toMilliseconds();
        
        HashMap<int, struct WheelNote>::Iterator iter (notesOn);
        while (iter.next()) {
            
            int noteNumber = iter.getKey();
            struct WheelNote wNote = iter.getValue();
            float gain=1.0;
            
            if (wNote.attacking)
            {
                DBG("attacking");
                if ( now > (wNote.noteOnTime+attackTimeInMs))
                {
                    //attack is done, let's note it
                    wNote.attacking=false;
                    DBG("attacking - done");
                }
                else{
                    //calculate the gain to apply for this particular time of the attacj
                    gain= (now - wNote.noteOnTime) / attackTimeInMs;
                    DBG("attacking ....");
                }
                    
            }
            else if (wNote.releasing)
            {
                DBG("releasing");
                if (now > (wNote.noteOffTime+releaseTimeInMs))
                {
                    //release is done, let kill the note
                    //forcing gain to 0
                    gain=0.0;
                    notesOn.remove(noteNumber);
                     DBG("kill");
                }
                else {
                    //calculate the gain to apply
                    gain = ((wNote.noteOffTime+releaseTimeInMs) - now) / releaseTimeInMs;
                    DBG("releasing ....");
                }
            }
            
            DBG(gain);
            
            //compute the sample for this note
            sample += sample + gain * getSineValue(MidiMessage::getMidiNoteInHertz(wNote.note),currentPhase,0);
            
        }
        
        currentPhase += (1/sampleRate);
        
        for (int j = outputBuffer.getNumChannels(); --j >= 0;)
            outputBuffer.addSample(j, startSample, sample);
        ++startSample;
        
    }


}

float WheelSineGenerator::getSineValue(double frequency, double time, double phase)
{
    return std::sin((2.0 * double_Pi * frequency * time) + phase);
}


void WheelSineGenerator::handleMidiEvent (const MidiMessage& m)
{

    if (m.isNoteOn())
    {
        struct WheelNote wNote;
        wNote.note=m.getNoteNumber();
        wNote.attacking=true;
        wNote.releasing=false;
        wNote.noteOnTime=Time::getCurrentTime().toMilliseconds();
        wNote.noteOffTime=Time::getCurrentTime().toMilliseconds();
        
        notesOn.set(wNote.note,wNote);

    }
    else if (m.isNoteOff())
    {
        struct WheelNote wNote;
        wNote = notesOn.operator[](m.getNoteNumber());
        wNote.attacking=false;
        wNote.releasing=true;
        wNote.noteOffTime=Time::getCurrentTime().toMilliseconds();
        
        notesOn.set(wNote.note,wNote);

    }
    else if (m.isAllNotesOff() || m.isAllSoundOff())
    {
        //TODO
    }
    else if (m.isPitchWheel())
    {
        //TODO
        //const int channel = m.getChannel();
        //const int wheelPos = m.getPitchWheelValue();
        //lastPitchWheelValues [channel - 1] = wheelPos;
        //handlePitchWheel (channel, wheelPos);
    }
    else if (m.isAftertouch())
    {
        //TODO
        //handleAftertouch (m.getChannel(), m.getNoteNumber(), m.getAfterTouchValue());
    }
    else if (m.isController())
    {
        //TODO
        //handleController (m.getChannel(), m.getControllerNumber(), m.getControllerValue());
    }
}