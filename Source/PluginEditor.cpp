/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ToneWheelSineAudioProcessorEditor::ToneWheelSineAudioProcessorEditor (ToneWheelSineAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    DBG("New ToneWheelSineAudioProcessorEditor");
    
    sliders.add(&subSlider);
    sliders.add(&slider5);
    sliders.add(&mainSlider);
    sliders.add(&slider8);
    sliders.add(&slider12);
    sliders.add(&slider15);
    sliders.add(&slider17);
    sliders.add(&slider19);
    sliders.add(&slider22);
    
    phaseSliders.add(&subPhaseSlider);
    phaseSliders.add(&phaseSlider5);
    phaseSliders.add(&mainPhaseSlider);
    phaseSliders.add(&phaseSlider8);
    phaseSliders.add(&phaseSlider12);
    phaseSliders.add(&phaseSlider15);
    phaseSliders.add(&phaseSlider17);
    phaseSliders.add(&phaseSlider19);
    phaseSliders.add(&phaseSlider22);
   
    waveSliders.add(&subWaveSlider);
    waveSliders.add(&waveSlider5);
    waveSliders.add(&mainWaveSlider);
    waveSliders.add(&waveSlider8);
    waveSliders.add(&waveSlider12);
    waveSliders.add(&waveSlider15);
    waveSliders.add(&waveSlider17);
    waveSliders.add(&waveSlider19);
    waveSliders.add(&waveSlider22);
    
    tremSliders.add(&subTremSlider);
    tremSliders.add(&tremSlider5);
    tremSliders.add(&mainTremSlider);
    tremSliders.add(&tremSlider8);
    tremSliders.add(&tremSlider12);
    tremSliders.add(&tremSlider15);
    tremSliders.add(&tremSlider17);
    tremSliders.add(&tremSlider19);
    tremSliders.add(&tremSlider22);
    
    setSize (300, 400);
    
    for (int i=0;i<sliders.size();++i)
    {
        Slider *s = sliders.getUnchecked(i);
        initSlider( *s,i);
        s->addListener(this);
        addAndMakeVisible(s);
        
    }
    
    for (int i=0;i<phaseSliders.size();++i)
    {
        Slider *s = phaseSliders.getUnchecked(i);
        initPhaseSlider( *s,i);
        s->addListener(this);
        addAndMakeVisible(s);
        
    }
    
    for (int i=0;i<waveSliders.size();++i)
    {
        Slider *s = waveSliders.getUnchecked(i);
        initWaveSlider( *s,i);
        s->addListener(this);
        addAndMakeVisible(s);
        
    }
    
    for (int i=0;i<tremSliders.size();++i)
    {
        Slider *s = tremSliders.getUnchecked(i);
        initTremSlider( *s,i);
        s->addListener(this);
        addAndMakeVisible(s);
        
    }
    
    
  
    
    harmonicStyle.setSliderStyle(Slider::LinearVertical);
    harmonicStyle.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    harmonicStyle.setRange(0.0, 1.0, 1.0);
    if (processor.isInitialState) harmonicStyle.setValue(1.0);
    harmonicStyle.setSize(10, 30);
    harmonicStyle.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    harmonicStyle.addListener(this);
    addAndMakeVisible(&harmonicStyle);
    
    tremoloSpeedSlider.setSliderStyle (Slider::Rotary);
    tremoloSpeedSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::slategrey);
    tremoloSpeedSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
    tremoloSpeedSlider.setRange(0.01, 1.0, 0.01);
    tremoloSpeedSlider.setTextValueSuffix ("Tremolo Speed");
    tremoloSpeedSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    if (processor.isInitialState) tremoloSpeedSlider.setValue(0.5);
    tremoloSpeedSlider.addListener(this);
    addAndMakeVisible(&tremoloSpeedSlider);
    
    tremoloDepthSlider.setSliderStyle (Slider::Rotary);
    tremoloDepthSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::slategrey);
    tremoloDepthSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
    tremoloDepthSlider.setRange(0.0, 1.0, 0.01);
    tremoloDepthSlider.setTextValueSuffix ("Tremolo Depth");
    tremoloDepthSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    if (processor.isInitialState) tremoloDepthSlider.setValue(0.5);
    tremoloDepthSlider.addListener(this);
    addAndMakeVisible(&tremoloDepthSlider);
    
    volumeSlider.setSliderStyle (Slider::Rotary);
    volumeSlider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::slategrey);
    volumeSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setTextValueSuffix ("MainVolume");
    volumeSlider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    if (processor.isInitialState) volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(&volumeSlider);

    
}

ToneWheelSineAudioProcessorEditor::~ToneWheelSineAudioProcessorEditor()
{
    DBG("Delete ToneWheelSineAudioProcessorEditor");
}

//==============================================================================
void ToneWheelSineAudioProcessorEditor::paint (Graphics& g)
{
   
    DBG("ToneWheelSineAudioProcessorEditor::paint");
    
    g.setGradientFill (ColourGradient (Colours::grey, 0, 0,
                                       Colours::black, 0, (float) getHeight(), false));
    g.fillAll();

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("ToneWheelSine", 0, 0, getWidth(), 30, Justification::centred, 1);
    
    g.drawLine(0, 25, 300, 25);
    g.drawFittedText ("Phase", 0, 28, getWidth(), 15, Justification::left, 1);
    
    g.drawFittedText("S", 7, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("5", 37, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("M", 67, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("8", 97, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("12", 127, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("15", 157, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("17", 187, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("19", 217, 275, 30, 30, Justification::centred, 1);
    g.drawFittedText("22", 247, 275, 30, 30, Justification::centred, 1);
    
    g.drawFittedText ("Wave", 0, 175, getWidth(), 15, Justification::left, 1);
    
    for (int i=0;i<waveSliders.size();++i)
    {
        g.drawFittedText("^", (10+(i*30)+2), 190, 20, 10, Justification::centred, 1);
    }
    
    for (int i=0;i<waveSliders.size();++i)
    {
        g.drawFittedText("~", (10+(i*30)+2), 230, 20, 10, Justification::centred, 1);
    }
    
    
    g.drawFittedText ("Tremolo", 0, 240, getWidth(), 15, Justification::left, 1);
    
    g.drawLine(0, 300, 300, 300);
    
    g.drawFittedText("Harmonic", 0, 300, 100, 30, Justification::centred, 1);
    g.drawFittedText("Tremolo", 100, 300, 100, 30, Justification::centred, 1);
    g.drawFittedText("Volume", 200, 300, 100, 30, Justification::centred, 1);
    
    g.drawFittedText("Pure", 0, 320, 100, 30, Justification::centred, 1);
    g.drawFittedText("Tempered", 0, 370, 100, 30, Justification::centred, 1);
    
    g.drawFittedText("Speed", 130, 330, 80, 20, Justification::left, 1);
    g.drawFittedText("Depth", 130, 360, 80, 20, Justification::left, 1);
    
    reloadValues();
}

void ToneWheelSineAudioProcessorEditor::resized()
{
    DBG("ToneWheelSineAudioProcessorEditor::resized");
    for (int i=0;i<sliders.size();++i)
    {
        Slider *s = sliders.getUnchecked(i);
        s->setName(sliderNames[i]);
        s->setBounds((10+(i*30)+2), 68, 20, 100);
    }
    
    for (int i=0;i<phaseSliders.size();++i)
    {
        Slider *s = phaseSliders.getUnchecked(i);
        s->setName(phaseSliderNames[i]);
        s->setBounds((10+(i*30)+2), 45, 20, 20);
    }
    
    for (int i=0;i<waveSliders.size();++i)
    {
        Slider *s = waveSliders.getUnchecked(i);
        s->setName(waveSliderNames[i]);
        s->setBounds((10+(i*30)+7), 200, 20, 30);
    }
    
    for (int i=0;i<tremSliders.size();++i)
    {
        Slider *s = tremSliders.getUnchecked(i);
        s->setName(tremSliderNames[i]);
        s->setBounds((10+(i*30)+2), 260, 20, 20);
    }
    
    harmonicStyle.setBounds(45, 345, 20, 30);
    tremoloSpeedSlider.setBounds(110, 330, 20, 20);
    tremoloDepthSlider.setBounds(110, 360, 20, 20);
    volumeSlider.setBounds(200, 340, 100, 50);
    
    
   
}

void ToneWheelSineAudioProcessorEditor::initSlider(Slider& slider, int position)
{
    slider.setSliderStyle (Slider::LinearBarVertical);
    slider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    slider.setRange(0.0, 1.0, 0.01);
    slider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    slider.setTextValueSuffix ("Bar");
    if (processor.isInitialState) slider.setValue(0.0);
    
}

void ToneWheelSineAudioProcessorEditor::initPhaseSlider(Slider& slider, int position)
{
    slider.setSliderStyle (Slider::Rotary);
    slider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::slategrey);
    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
    slider.setRange(0.0, 2*double_Pi, 0.01);
    slider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    slider.setTextValueSuffix ("Rotary");
    if (processor.isInitialState) slider.setValue(0.0);
    
}

void ToneWheelSineAudioProcessorEditor::initWaveSlider(Slider& slider, int position)
{
    slider.setSliderStyle (Slider::LinearVertical);
    slider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
    slider.setRange(0.0, 1.0, 1.0);
    if (processor.isInitialState) slider.setValue(0.0);
    slider.setSize(10, 30);
    slider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    
}

void ToneWheelSineAudioProcessorEditor::initTremSlider(Slider& slider, int position)
{
    slider.setSliderStyle (Slider::Rotary);
    slider.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::slategrey);
    slider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::white);
    slider.setRange(0.0, 1.0, 0.01);
    slider.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    slider.setTextValueSuffix ("Rotary");
    if (processor.isInitialState) slider.setValue(0.0);
    
}

void ToneWheelSineAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (&volumeSlider==slider)
    {
        //Volume Slider
        //DBG("Vol");
        processor.mainVolume=volumeSlider.getValue();
    }
    else if (&harmonicStyle==slider)
    {
        //Harmonic Style Slider
        //DBG("Harm");
        processor.harmonicStyle=harmonicStyle.getValue();
    }
    else if (&tremoloDepthSlider==slider){
        processor.tremoloDepth=tremoloDepthSlider.getValue();
    }
    else if (&tremoloSpeedSlider==slider){
        processor.tremoloSpeed=tremoloSpeedSlider.getValue();
    }
    else
    {
        juce::String sliderName = slider->getName();
        float value;
        if (sliderName.startsWith("phase")){
            //one of the phase sliders
            //DBG("Phase");
            value = slider->getValue();
            float* sliderValue = processor.slidersPhaseValues.operator[](sliderName);
            *sliderValue = value;
        }
        else if (sliderName.startsWith("wave")){
            //one of the phase sliders
            //DBG("Phase");
            value = slider->getValue();
            int* sliderValue = processor.slidersWaveValues.operator[](sliderName);
            *sliderValue = value;
        }
        else if (sliderName.startsWith("trem")){
            //one of the phase sliders
            //DBG("Phase");
            value = slider->getValue();
            float* sliderValue = processor.slidersTremValues.operator[](sliderName);
            *sliderValue = value;
        }
        else {
            //one of the bar sliders
            //DBG("BAR");
            value = slider->getValue();
            float* sliderValue = processor.slidersValues.operator[](sliderName);
            *sliderValue = value;
           
        }
        //notify modification
        processor.notifyChangedParameter(sliderName,value);
    }
}

void ToneWheelSineAudioProcessorEditor::reloadValues()
{
    DBG("ToneWheelSineAudioProcessorEditor::reloadValues");
    
    //Bar sliders ==============
    subSlider.setValue(processor.subSliderValue);
    slider5.setValue(processor.slider5Value);
    mainSlider.setValue(processor.mainSliderValue);
    slider8.setValue(processor.slider8Value);
    slider12.setValue(processor.slider12Value);
    slider15.setValue(processor.slider15Value);
    slider17.setValue(processor.slider17Value);
    slider19.setValue(processor.slider19Value);
    slider22.setValue(processor.slider22Value);
   
    //Phase sliders ==============
    subPhaseSlider.setValue(processor.subSliderPhaseValue);
    phaseSlider5.setValue(processor.slider5PhaseValue);
    mainPhaseSlider.setValue(processor.mainSliderPhaseValue);
    phaseSlider8.setValue(processor.slider8PhaseValue);
    phaseSlider12.setValue(processor.slider12PhaseValue);
    phaseSlider15.setValue(processor.slider15PhaseValue);
    phaseSlider17.setValue(processor.slider17PhaseValue);
    phaseSlider19.setValue(processor.slider19PhaseValue);
    phaseSlider22.setValue(processor.slider22PhaseValue);
    
    //Wave sliders ==============
    subWaveSlider.setValue(processor.subSliderWaveValue);
    waveSlider5.setValue(processor.slider5WaveValue);
    mainWaveSlider.setValue(processor.mainSliderWaveValue);
    waveSlider8.setValue(processor.slider8WaveValue);
    waveSlider12.setValue(processor.slider12WaveValue);
    waveSlider15.setValue(processor.slider15WaveValue);
    waveSlider17.setValue(processor.slider17WaveValue);
    waveSlider19.setValue(processor.slider19WaveValue);
    waveSlider22.setValue(processor.slider22WaveValue);
    
    //Tremolo sliders ==============
    subTremSlider.setValue(processor.subSliderTremValue);
    tremSlider5.setValue(processor.slider5TremValue);
    mainTremSlider.setValue(processor.mainSliderTremValue);
    tremSlider8.setValue(processor.slider8TremValue);
    tremSlider12.setValue(processor.slider12TremValue);
    tremSlider15.setValue(processor.slider15TremValue);
    tremSlider17.setValue(processor.slider17TremValue);
    tremSlider19.setValue(processor.slider19TremValue);
    tremSlider22.setValue(processor.slider22TremValue);
   
   
    //Other controls
    volumeSlider.setValue(processor.mainVolume);
    harmonicStyle.setValue(processor.harmonicStyle);
    tremoloSpeedSlider.setValue(processor.tremoloSpeed);
    tremoloDepthSlider.setValue(processor.tremoloDepth);
    
    processor.isInitialState=false;
    //valuesSet = true;
    //resized();
    
}



