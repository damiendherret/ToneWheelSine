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

void WheelSineGenerator::initWheel(
                                   double initialSampleRate,
                                   HashMap<String, float*> *sliders,
                                   HashMap<String, float*> *phaseSliders,
                                   HashMap<String, int*> *waveSliders,
                                   HashMap<String, float*> *tremSliders,
                                   int* pHarmonicStyle,
                                   float* pTremoloSpeed,
                                   float* pTremoloDepth)
{
    //ptr to harmonics
    harmonicStyle = pHarmonicStyle;
    
    //ptr to trem speed
    tremoloSpeed = pTremoloSpeed;
    
    //ptr to harmonics
    tremoloDepth = pTremoloDepth;
    
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
    
    //ptr to waveforms
    slidersWaveValues.clear();
    HashMap<String, int*>::Iterator iter3 (*waveSliders);
    while (iter3.next())
    {
        String key = iter3.getKey();
        int* sliderValue = iter3.getValue();
        slidersWaveValues.set(key,sliderValue);
    }
    
    //ptr to tremolos
    slidersTremValues.clear();
    HashMap<String, float*>::Iterator iter4 (*tremSliders);
    while (iter4.next())
    {
        String key = iter4.getKey();
        float* sliderValue = iter4.getValue();
        slidersTremValues.set(key,sliderValue);
    }
   
	//frequency = 440;
    sampleRate = initialSampleRate;
	currentPhase = 0;

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
    
    //wave sliders management
    else if (parameterName.equalsIgnoreCase("waveSubSlider")){
        waveSubSlider = *slidersWaveValues.operator[]("waveSubSlider");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider5")){
        waveSlider5 = *slidersWaveValues.operator[]("waveSlider5");
    }
    else if (parameterName.equalsIgnoreCase("waveMainSlider")){
        waveMainSlider = *slidersWaveValues.operator[]("waveMainSlider");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider8")){
        waveSlider8 = *slidersWaveValues.operator[]("waveSlider8");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider12")){
        waveSlider12 = *slidersWaveValues.operator[]("waveSlider12");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider15")){
        waveSlider15 = *slidersWaveValues.operator[]("waveSlider15");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider17")){
        waveSlider17 = *slidersWaveValues.operator[]("waveSlider17");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider19")){
        waveSlider19 = *slidersWaveValues.operator[]("waveSlider19");
    }
    else if (parameterName.equalsIgnoreCase("waveSlider22")){
        waveSlider22 = *slidersWaveValues.operator[]("waveSlider22");
    }
    
    //trem sliders management
    else if (parameterName.equalsIgnoreCase("tremSubSlider")){
        tremSubSlider = *slidersTremValues.operator[]("tremSubSlider");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider5")){
       tremSlider5 = *slidersTremValues.operator[]("tremSlider5");
    }
    else if (parameterName.equalsIgnoreCase("tremMainSlider")){
        tremMainSlider = *slidersTremValues.operator[]("tremMainSlider");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider8")){
        tremSlider8 = *slidersTremValues.operator[]("tremSlider8");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider12")){
        tremSlider12 = *slidersTremValues.operator[]("tremSlider12");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider15")){
        tremSlider15 = *slidersTremValues.operator[]("tremSlider15");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider17")){
        tremSlider17 = *slidersTremValues.operator[]("tremSlider17");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider19")){
        tremSlider19 = *slidersTremValues.operator[]("tremSlider19");
    }
    else if (parameterName.equalsIgnoreCase("tremSlider22")){
        tremSlider22 = *slidersTremValues.operator[]("tremSlider22");
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
        calculus += subSlider * getValue(MidiMessage::getMidiNoteInHertz(note-12),currentPhase,phaseSubSlider,waveSubSlider);
        calculus += slider5 * getValue(MidiMessage::getMidiNoteInHertz(note+7),currentPhase,phaseSlider5,waveSlider5);
        calculus += mainSlider * getValue(MidiMessage::getMidiNoteInHertz(note),currentPhase,phaseMainSlider,waveMainSlider);
        calculus += slider8 * getValue(MidiMessage::getMidiNoteInHertz(note+12),currentPhase,phaseSlider8,waveSlider8);
        calculus += slider12 * getValue(MidiMessage::getMidiNoteInHertz(note+19),currentPhase,phaseSlider12,waveSlider12);
        calculus += slider15 * getValue(MidiMessage::getMidiNoteInHertz(note+24),currentPhase,phaseSlider15,waveSlider15);
        calculus += slider17 * getValue(MidiMessage::getMidiNoteInHertz(note+28),currentPhase,phaseSlider17,waveSlider17);
        calculus += slider19 * getValue(MidiMessage::getMidiNoteInHertz(note+31),currentPhase,phaseSlider19,waveSlider19);
        calculus += slider22 * getValue(MidiMessage::getMidiNoteInHertz(note+36),currentPhase,phaseSlider22,waveSlider22);
    }
    else {
        
        //pure harmonics
        double frequency = MidiMessage::getMidiNoteInHertz(note);

        calculus += subSlider * getValue(frequency/2,currentPhase,phaseSubSlider,waveSubSlider);
        calculus += slider5 * getValue(frequency*(1.5f),currentPhase,phaseSlider5,waveSlider5);
        calculus += mainSlider * getValue(frequency,currentPhase,phaseMainSlider,waveMainSlider);
        calculus += slider8 * getValue(frequency*2,currentPhase,phaseSlider8,waveSlider8);
        calculus += slider12 * getValue(frequency*3,currentPhase,phaseSlider12,waveSlider12);
        calculus += slider15 * getValue(frequency*4,currentPhase,phaseSlider15,waveSlider15);
        calculus += slider17 * getValue(frequency*5,currentPhase,phaseSlider17,waveSlider17);
        calculus += slider19 * getValue(frequency*6,currentPhase,phaseSlider19,waveSlider19);
        calculus += slider22 * getValue(frequency*8,currentPhase,phaseSlider22,waveSlider22);
        
    }

    return calculus;
}

float WheelSineGenerator::getValue(double frequency, double time, double phase, int waveform)
{
    switch (waveform) {
        case 0:
            return getSineValue(frequency,time,phase);
            break;
        case 1:
            return getTriangleValue(frequency,time,phase);
            break;    
        default:
            return getSineValue(frequency,time,phase);
            break;
    }
}

float WheelSineGenerator::getSineValue(double frequency, double time, double phase)
{
    return std::sin((2.0 * double_Pi * frequency * time) + phase);
}

float WheelSineGenerator::getTriangleValue(double frequency, double time, double phase)
{
    while (time > sampleRate/frequency)
    {
        time = time - (1/frequency);
    }

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