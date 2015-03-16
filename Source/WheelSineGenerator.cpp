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
   
	//frequency = 440;
    sampleRate = initialSampleRate;
	currentPhase = 0;
	phasePerSample = 0.0;
	amplitude = 0.1f;
    
    attackTimeInMs = 100;
    releaseTimeInMs = 100;
}

void WheelSineGenerator::setParameter(String parameterName, float parameterValue){
    
    
    // gain sliders management
    if (parameterName.equalsIgnoreCase("subSlider")){
        subSlider = *slidersValues.operator[]("subSlider");
    }
    else if (parameterName.equalsIgnoreCase("slider5")){
        slider5 = *slidersValues.operator[]("slider5");
    }
    else if (parameterName.equalsIgnoreCase("mainSlider")){
        mainSlider = *slidersValues.operator[]("mainSlider");
    }
    else if (parameterName.equalsIgnoreCase("slider8")){
        slider8 = *slidersValues.operator[]("slider8");
    }
    else if (parameterName.equalsIgnoreCase("slider12")){
        slider12 = *slidersValues.operator[]("slider12");
    }
    else if (parameterName.equalsIgnoreCase("slider15")){
        slider15 = *slidersValues.operator[]("slider15");
    }
    else if (parameterName.equalsIgnoreCase("slider17")){
        slider17 = *slidersValues.operator[]("slider17");
    }
    else if (parameterName.equalsIgnoreCase("slider19")){
        slider19 = *slidersValues.operator[]("slider19");
    }
    else if (parameterName.equalsIgnoreCase("slider22")){
        slider22 = *slidersValues.operator[]("slider22");
    }
    
    //phase sliders management
    else if (parameterName.equalsIgnoreCase("phaseSubSlider")){
        phaseSubSlider = *slidersPhaseValues.operator[]("phaseSubSlider");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider5")){
        phaseSlider5 = *slidersPhaseValues.operator[]("phaseSlider5");
    }
    else if (parameterName.equalsIgnoreCase("phaseMainSlider")){
        phaseMainSlider = *slidersPhaseValues.operator[]("phaseMainSlider");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider8")){
        phaseSlider8 = *slidersPhaseValues.operator[]("phaseSlider8");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider12")){
        phaseSlider12 = *slidersPhaseValues.operator[]("phaseSlider12");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider15")){
        phaseSlider15 = *slidersPhaseValues.operator[]("phaseSlider15");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider17")){
        phaseSlider17 = *slidersPhaseValues.operator[]("phaseSlider17");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider19")){
        phaseSlider19 = *slidersPhaseValues.operator[]("phaseSlider19");
    }
    else if (parameterName.equalsIgnoreCase("phaseSlider22")){
        phaseSlider22 = *slidersPhaseValues.operator[]("phaseSlider22");
    }
    

    
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
                    //calculate the gain to apply for this particular time of the attac
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
            
            //final
            sample += amplitude * gain * computeNote(wNote.note);
            
            //debug
            //sample += amplitude * gain * getSineValue(MidiMessage::getMidiNoteInHertz(wNote.note),currentPhase,0);
        
        }
        
        currentPhase += (1/sampleRate);

        
        for (int j = outputBuffer.getNumChannels(); --j >= 0;)
        {
            //DBG(sample);
            outputBuffer.addSample(j, startSample, sample);
        }
        ++startSample;
        
    }


}


float WheelSineGenerator::computeNote(int note)
{
    float calculus=0.0;
    if (*harmonicStyle==1)
    {
        //tempered harmonics
        calculus += subSlider * getSineValue(MidiMessage::getMidiNoteInHertz(note-12),currentPhase,phaseSubSlider);
        calculus += slider5 * getSineValue(MidiMessage::getMidiNoteInHertz(note+7),currentPhase,phaseSlider5);
        calculus += mainSlider * getSineValue(MidiMessage::getMidiNoteInHertz(note),currentPhase,phaseMainSlider);
        calculus += slider8 * getSineValue(MidiMessage::getMidiNoteInHertz(note+12),currentPhase,phaseSlider8);
        calculus += slider12 * getSineValue(MidiMessage::getMidiNoteInHertz(note+19),currentPhase,phaseSlider12);
        calculus += slider15 * getSineValue(MidiMessage::getMidiNoteInHertz(note+24),currentPhase,phaseSlider15);
        calculus += slider17 * getSineValue(MidiMessage::getMidiNoteInHertz(note+28),currentPhase,phaseSlider17);
        calculus += slider19 * getSineValue(MidiMessage::getMidiNoteInHertz(note+31),currentPhase,phaseSlider19);
        calculus += slider22 * getSineValue(MidiMessage::getMidiNoteInHertz(note+36),currentPhase,phaseSlider22);
    }
    else {
        
        //pure harmonics
        double frequency = MidiMessage::getMidiNoteInHertz(note);

        calculus += subSlider * getSineValue(frequency/2,currentPhase,phaseSubSlider);
        calculus += slider5 * getSineValue(frequency*(1.5f),currentPhase,phaseSlider5);
        calculus += mainSlider * getSineValue(frequency,currentPhase,phaseMainSlider);
        calculus += slider8 * getSineValue(frequency*2,currentPhase,phaseSlider8);
        calculus += slider12 * getSineValue(frequency*3,currentPhase,phaseSlider12);
        calculus += slider15 * getSineValue(frequency*4,currentPhase,phaseSlider15);
        calculus += slider17 * getSineValue(frequency*5,currentPhase,phaseSlider17);
        calculus += slider19 * getSineValue(frequency*6,currentPhase,phaseSlider19);
        calculus += slider22 * getSineValue(frequency*8,currentPhase,phaseSlider22);
        
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