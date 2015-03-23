#include "WheelSineGenerator.h"
#include <cmath> 

struct WheelNote
{
    int note;
    bool attacking;
    bool releasing;
    double noteGain;
    
};

WheelSineGenerator::WheelSineGenerator()
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
    
    notesOn.clear();
    
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
        setParameter(key, *iter.getValue());
    }
    
    //ptr to phase
    slidersPhaseValues.clear();
    HashMap<String, float*>::Iterator iter2 (*phaseSliders);
    while (iter2.next())
    {
        String key = iter2.getKey();
        float* sliderValue = iter2.getValue();
        slidersPhaseValues.set(key,sliderValue);
        setParameter(key, *iter2.getValue());
    }
    
    //ptr to waveforms
    slidersWaveValues.clear();
    HashMap<String, int*>::Iterator iter3 (*waveSliders);
    while (iter3.next())
    {
        String key = iter3.getKey();
        int* sliderValue = iter3.getValue();
        slidersWaveValues.set(key,sliderValue);
        setParameter(key, *iter3.getValue());
    }
    
    //ptr to tremolos
    slidersTremValues.clear();
    HashMap<String, float*>::Iterator iter4 (*tremSliders);
    while (iter4.next())
    {
        String key = iter4.getKey();
        float* sliderValue = iter4.getValue();
        slidersTremValues.set(key,sliderValue);
        setParameter(key, *iter4.getValue());
    }
   
	//frequency = 440;
    if (initialSampleRate != 0)
    {
        sampleRate = initialSampleRate;
    }
    
	currentPhase = 0;
    
    /*-------------------------------------
     Param that can be changed
     ------------------------------------*/
    amplitude = 0.5f;
    gainOn = 1.01;
    gainOff = 0.99;
    
    tremBaseFrequency = 5; //5Hz
    
    //DEBUG ------------------
    //debugParameters();
    
    ready=true;
    
}

void WheelSineGenerator::setParameter(String parameterName, float parameterValue){
    
    
    /*-------------------------------------
     Gain sliders Management
     ------------------------------------*/
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
    
    /*-------------------------------------
     phase sliders management
     ------------------------------------*/
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
    
    /*-------------------------------------
     wave sliders management
     ------------------------------------*/
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
    
    /*-------------------------------------
     trem sliders management
     ------------------------------------*/
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
    if (!ready){
        //DBG("Called while not ready");
        return;
    }
    
    /*-------------------------------------
     Handle MIDI messages
     ------------------------------------*/
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        handleMidiEvent(m);
    }
    
    /*-------------------------------------
     Generate sounds and mix
     ------------------------------------*/
    for (int i = 0; i < numSamples; ++i)
    {
        float sample = 0;
        HashMap<int, struct WheelNote>::Iterator iter (notesOn);
        
        while (iter.next())
        {
            int noteNumber = iter.getKey();
            struct WheelNote wNote = iter.getValue();
            double gain=1.0;
            
            /*-------------------------------------
             Gestion Attack and release
             ------------------------------------*/
            if (wNote.attacking)
            {
                wNote.noteGain = wNote.noteGain * gainOn;
                if (wNote.noteGain>1.0){
                    wNote.noteGain = 1;
                    wNote.attacking = false;
                }
                gain = wNote.noteGain;
                notesOn.set(wNote.note,wNote);
            }
            else if (wNote.releasing)
            {
                wNote.noteGain = wNote.noteGain * gainOff;
                notesOn.set(wNote.note,wNote);
                gain = wNote.noteGain;
                if (wNote.noteGain<0.005){
                    gain = 0;
                    notesOn.remove(noteNumber);
                }
            }
            
            /*-------------------------------------
             Compute sample
             ------------------------------------*/
            sample += amplitude
                        * gain
                        * computeNote(wNote.note);
        
        }
        
        /*-------------------------------------
         Prepare next sample
         ------------------------------------*/
        currentPhase += (1/sampleRate);

        /*-------------------------------------
         Writing Output
         ------------------------------------*/
        for (int j = outputBuffer.getNumChannels(); --j >= 0;)
        {

            outputBuffer.addSample(j, startSample, sample);
        }
        ++startSample;
        
    }
}


float WheelSineGenerator::computeNote(int note)
{
    float calculus=0.0;
    float tremGain = getTremoloGain(currentPhase);
    
    if (*harmonicStyle==0)
    {
        /*-------------------------------------
         Tempered harmonics
         Harmonics are notes
         ------------------------------------*/
        calculus += (1 - tremSubSlider * tremGain) * subSlider * getValue(MidiMessage::getMidiNoteInHertz(note-12),currentPhase,phaseSubSlider,waveSubSlider);
        calculus += (1 - tremSlider5 * tremGain) * slider5 * getValue(MidiMessage::getMidiNoteInHertz(note+7),currentPhase,phaseSlider5,waveSlider5);
        calculus += (1 - tremMainSlider * tremGain) * mainSlider * getValue(MidiMessage::getMidiNoteInHertz(note),currentPhase,phaseMainSlider,waveMainSlider);
        calculus += (1 - tremSlider8 * tremGain) * slider8 * getValue(MidiMessage::getMidiNoteInHertz(note+12),currentPhase,phaseSlider8,waveSlider8);
        calculus += (1 - tremSlider12 * tremGain) * slider12 * getValue(MidiMessage::getMidiNoteInHertz(note+19),currentPhase,phaseSlider12,waveSlider12);
        calculus += (1 - tremSlider15 * tremGain) * slider15 * getValue(MidiMessage::getMidiNoteInHertz(note+24),currentPhase,phaseSlider15,waveSlider15);
        calculus += (1 - tremSlider17 * tremGain) * slider17 * getValue(MidiMessage::getMidiNoteInHertz(note+28),currentPhase,phaseSlider17,waveSlider17);
        calculus += (1 - tremSlider19 * tremGain) * slider19 * getValue(MidiMessage::getMidiNoteInHertz(note+31),currentPhase,phaseSlider19,waveSlider19);
        calculus += (1 - tremSlider22 * tremGain) * slider22 * getValue(MidiMessage::getMidiNoteInHertz(note+36),currentPhase,phaseSlider22,waveSlider22);
    }
    else {
        
        /*-------------------------------------
         Pure harmonics
         Harmonics frequency multiples
         ------------------------------------*/
        double frequency = MidiMessage::getMidiNoteInHertz(note);

        calculus += (1 - tremSubSlider * tremGain) * subSlider * getValue(frequency/2,currentPhase,phaseSubSlider,waveSubSlider);
        calculus += (1 - tremSlider5 * tremGain) * slider5 * getValue(frequency*(1.5f),currentPhase,phaseSlider5,waveSlider5);
        calculus += (1 - tremMainSlider * tremGain) * mainSlider * getValue(frequency,currentPhase,phaseMainSlider,waveMainSlider);
        calculus += (1 - tremSlider8 * tremGain) * slider8 * getValue(frequency*2,currentPhase,phaseSlider8,waveSlider8);
        calculus += (1 - tremSlider12 * tremGain) * slider12 * getValue(frequency*3,currentPhase,phaseSlider12,waveSlider12);
        calculus += (1 - tremSlider15 * tremGain) * slider15 * getValue(frequency*4,currentPhase,phaseSlider15,waveSlider15);
        calculus += (1 - tremSlider17 * tremGain) * slider17 * getValue(frequency*5,currentPhase,phaseSlider17,waveSlider17);
        calculus += (1 - tremSlider19 * tremGain) * slider19 * getValue(frequency*6,currentPhase,phaseSlider19,waveSlider19);
        calculus += (1 - tremSlider22 * tremGain) * slider22 * getValue(frequency*8,currentPhase,phaseSlider22,waveSlider22);
        
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
    double period = (1 / frequency);
    double tSurA = time / period;
    double xt = std::abs(2 * (tSurA - floor(tSurA + 0.5)));
    
    return 2 * (xt - 0.5);

}

float WheelSineGenerator::getTremoloGain(double time){
    return *tremoloDepth * getSineValue((tremBaseFrequency * *tremoloSpeed), time, 0);
}

void WheelSineGenerator::handleMidiEvent (const MidiMessage& m)
{

    if (m.isNoteOn())
    {
        struct WheelNote wNote;
        wNote.note=m.getNoteNumber();
        wNote.attacking=true;
        wNote.releasing=false;
        wNote.noteGain = 0.05;
        
        notesOn.set(wNote.note,wNote);

    }
    else if (m.isNoteOff())
    {
        struct WheelNote wNote;
        wNote = notesOn.operator[](m.getNoteNumber());
        wNote.attacking=false;
        wNote.releasing=true;
      
        notesOn.set(wNote.note,wNote);

    }
    else if (m.isAllNotesOff() || m.isAllSoundOff())
    {
        //Not implemented
    }
    else if (m.isPitchWheel())
    {
        //Not implemented
        //const int channel = m.getChannel();
        //const int wheelPos = m.getPitchWheelValue();
        //lastPitchWheelValues [channel - 1] = wheelPos;
        //handlePitchWheel (channel, wheelPos);
    }
    else if (m.isAftertouch())
    {
        ////Not implemented
        //handleAftertouch (m.getChannel(), m.getNoteNumber(), m.getAfterTouchValue());
    }
    else if (m.isController())
    {
        ////Not implemented
        //handleController (m.getChannel(), m.getControllerNumber(), m.getControllerValue());
    }
}


void WheelSineGenerator::debugParameters()
{
    DBG("Sliders======================");
    DBG("subSlider");
    DBG(subSlider);
    DBG("slider5");
    DBG(slider5);
    DBG("mainSlider");
    DBG(mainSlider);
    DBG("slider8");
    DBG(slider8);
    DBG("slider12");
    DBG(slider12);
    DBG("slider15");
    DBG(slider15);
    DBG("slider17");
    DBG(slider17);
    DBG("slider19");
    DBG(slider19);
    DBG("slider22");
    DBG(slider22);

    DBG("Phase Sliders======================");
    DBG("phaseSubSlider");
    DBG(phaseSubSlider);
    DBG("phaseSlider5");
    DBG(phaseSlider5);
    DBG("phaseMainSlider");
    DBG(phaseMainSlider);
    DBG("phaseSlider8");
    DBG(phaseSlider8);
    DBG("phaseSlider12");
    DBG(phaseSlider12);
    DBG("phaseSlider15");
    DBG(phaseSlider15);
    DBG("phaseSlider17");
    DBG(phaseSlider17);
    DBG("phaseSlider19");
    DBG(phaseSlider19);
    DBG("phaseSlider22");
    DBG(phaseSlider22);
    
    DBG("Wave Sliders======================");
    DBG("waveSubSlider");
    DBG(waveSubSlider);
    DBG("waveSlider5");
    DBG(waveSlider5);
    DBG("waveMainSlider");
    DBG(waveMainSlider);
    DBG("waveSlider8");
    DBG(waveSlider8);
    DBG("waveSlider12");
    DBG(waveSlider12);
    DBG("waveSlider15");
    DBG(waveSlider15);
    DBG("waveSlider17");
    DBG(waveSlider17);
    DBG("waveSlider19");
    DBG(waveSlider19);
    DBG("waveSlider22");
    DBG(waveSlider22);

    DBG("Tremolo Sliders======================");
    DBG("tremSubSlider");
    DBG(tremSubSlider);
    DBG("tremSlider5");
    DBG(tremSlider5);
    DBG("tremMainSlider");
    DBG(tremMainSlider);
    DBG("tremSlider8");
    DBG(tremSlider8);
    DBG("tremSlider12");
    DBG(tremSlider12);
    DBG("tremSlider15");
    DBG(tremSlider15);
    DBG("tremSlider17");
    DBG(tremSlider17);
    DBG("tremSlider19");
    DBG(tremSlider19);
    DBG("tremSlider22");
    DBG(tremSlider22);
    
    DBG("Generals======================");
    DBG("harmonicStyle");
    DBG(*harmonicStyle);
    DBG("tremoloSpeed");
    DBG(*tremoloSpeed);
    DBG("tremoloDepth");
    DBG(*tremoloDepth);
    
   
    
    
}