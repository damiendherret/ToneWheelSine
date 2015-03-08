#include "WheelSineGenerator.h"

struct WheelNote
{
    int note;
    bool attacking;
    bool releasing;
    int64 noteOnTime;
    int64 noteOffTime;
    
};

WheelSineGenerator::WheelSineGenerator(/*ToneWheelSineAudioProcessor& p) : processor (p)*/)
{
}


WheelSineGenerator::~WheelSineGenerator()
{
}

void WheelSineGenerator::initWheel(double initialSampleRate, HashMap<String, float*> *sliders, HashMap<String, float*> *phaseSliders, int* pHarmonicStyle)
{
    //ptr to harmonics
    harmonicStyle = pHarmonicStyle;
    
    //Ptr to bar
    slidersValues.clear();
    HashMap<String, float*>::Iterator iter (*sliders);
    while (iter.next())
    {
        String key = iter.getKey();
        float* sliderValue = iter.getValue();
        slidersValues.set(key,sliderValue);
    }
    
    //ptr to phase
    slidersPhaseValues.clear();
    HashMap<String, float*>::Iterator iter2 (*phaseSliders);
    while (iter2.next())
    {
        String key = iter2.getKey();
        float* sliderValue = iter2.getValue();
        slidersPhaseValues.set(key,sliderValue);
    }
   
	frequency = 440;
    sampleRate = initialSampleRate;
	currentPhase = 0;
	phasePerSample = 0.0;
	amplitude = 0.8f;
    
    attackTimeInMs = 100;
    releaseTimeInMs = 100;
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
        while (iter.next())
        {
            
            int noteNumber = iter.getKey();
            struct WheelNote wNote = iter.getValue();
            double gain=1.0;
            
            if (wNote.attacking)
            {
                //DBG("attacking");
                if ( now > (wNote.noteOnTime+attackTimeInMs))
                {
                    //attack is done, let's note it
                    wNote.attacking=false;
                    //push modifications
                    notesOn.set(wNote.note,wNote);
                    //DBG("attacking - done");
                }
                else{
                    //calculate the gain to apply for this particular time of the attacj
                    gain = (now - wNote.noteOnTime) / attackTimeInMs;
                    //DBG((now - wNote.noteOnTime)/attackTimeInMs);
                    //DBG("attacking ....");
                }
                    
            }
            else if (wNote.releasing)
            {
                //DBG("releasing");
                if (now > (wNote.noteOffTime+releaseTimeInMs))
                {
                    //release is done, let kill the note
                    //forcing gain to 0
                    gain=0.0;
                    notesOn.remove(noteNumber);
                    //DBG("kill");
                }
                else {
                    //calculate the gain to apply
                    gain = ((wNote.noteOffTime+releaseTimeInMs) - now) / releaseTimeInMs;
                    //DBG("releasing ....");
                }
            }
            
            
            //compute the sample for this note
            //sample = sample + amplitude * (*sliderGain) * gain * getSineValue(MidiMessage::getMidiNoteInHertz(wNote.note),currentPhase,*phase);
            sample = sample + amplitude * gain * computeNote(wNote.note);
        }
        
        currentPhase += (1/sampleRate);
        
        for (int j = outputBuffer.getNumChannels(); --j >= 0;)
            outputBuffer.addSample(j, startSample, sample);
        ++startSample;
        
    }


}


float WheelSineGenerator::computeNote(int note)
{
    float calculus;
    if (*harmonicStyle==1){
        //tempered harmonics
        
        float* sliderGain /*= slidersValues.operator[]("mainSlider")*/;
        float* phase /*= slidersPhaseValues.operator[]("phaseMainSlider")*/;

        sliderGain = slidersValues.operator[]("subSlider");
        phase = slidersPhaseValues.operator[]("phaseSubSlider");
        calculus += (*sliderGain)
                    * getSineValue(MidiMessage::getMidiNoteInHertz(note-12),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider5");
        phase = slidersPhaseValues.operator[]("phaseSlider5");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+7),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("mainSlider");
        phase = slidersPhaseValues.operator[]("phaseMainSlider");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider8");
        phase = slidersPhaseValues.operator[]("phaseSlider8");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+12),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider12");
        phase = slidersPhaseValues.operator[]("phaseSlider12");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+19),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider15");
        phase = slidersPhaseValues.operator[]("phaseSlider15");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+24),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider17");
        phase = slidersPhaseValues.operator[]("phaseSlider17");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+28),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider19");
        phase = slidersPhaseValues.operator[]("phaseSlider19");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+31),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider22");
        phase = slidersPhaseValues.operator[]("phaseSlider22");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
                        * getSineValue(MidiMessage::getMidiNoteInHertz(note+36),currentPhase,*phase);
        
    }
    else {
        
        //pure harmonics
        //tempered harmonics
        
        float* sliderGain /*= slidersValues.operator[]("mainSlider")*/;
        float* phase /*= slidersPhaseValues.operator[]("phaseMainSlider")*/;
        double frequency = MidiMessage::getMidiNoteInHertz(note);
        
        
        sliderGain = slidersValues.operator[]("subSlider");
        phase = slidersPhaseValues.operator[]("phaseSubSlider");
        calculus += (*sliderGain)
        * getSineValue(frequency/2,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider5");
        phase = slidersPhaseValues.operator[]("phaseSlider5");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*(3/2),currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("mainSlider");
        phase = slidersPhaseValues.operator[]("phaseMainSlider");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider8");
        phase = slidersPhaseValues.operator[]("phaseSlider8");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*2,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider12");
        phase = slidersPhaseValues.operator[]("phaseSlider12");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*3,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider15");
        phase = slidersPhaseValues.operator[]("phaseSlider15");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*4,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider17");
        phase = slidersPhaseValues.operator[]("phaseSlider17");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*5,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider19");
        phase = slidersPhaseValues.operator[]("phaseSlider19");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*6,currentPhase,*phase);
        
        sliderGain = slidersValues.operator[]("slider22");
        phase = slidersPhaseValues.operator[]("phaseSlider22");
        if (*sliderGain!=0)
            calculus += (*sliderGain)
            * getSineValue(frequency*8,currentPhase,*phase);
        
        
        
    }

    return calculus;
}

float WheelSineGenerator::getSineValue(double frequency, double time, double phase)
{
    return std::sin((2.0 * double_Pi * frequency * time) + phase);
}


void WheelSineGenerator::handleMidiEvent (const MidiMessage& m)
{

    if (m.isNoteOn())
    {
        //DBG("Note ON");
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
        //DBG("Note OFF");
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