/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "WheelSineGenerator.h"



//==============================================================================
ToneWheelSineAudioProcessor::ToneWheelSineAudioProcessor()
{
    theWheelGenerator = new WheelSineGenerator();
    harmonicStyle=1;
    tremoloDepth=0.5;
    tremoloSpeed=0.5;
    
    subSliderValue=0;
    slider5Value=0;
    mainSliderValue=0;
    slider8Value=0;
    slider12Value=0;
    slider15Value=0;
    slider17Value=0;
    slider19Value=0;
    slider22Value=0;
    
    slidersValues.set("subSlider", &subSliderValue);
    slidersValues.set("slider5", &slider5Value);
    slidersValues.set("mainSlider", &mainSliderValue);
    slidersValues.set("slider8", &slider8Value);
    slidersValues.set("slider12", &slider12Value);
    slidersValues.set("slider15", &slider15Value);
    slidersValues.set("slider17", &slider17Value);
    slidersValues.set("slider19", &slider19Value);
    slidersValues.set("slider22", &slider22Value);
    
    subSliderPhaseValue=0;
    slider5PhaseValue=0;
    mainSliderPhaseValue=0;
    slider8PhaseValue=0;
    slider12PhaseValue=0;
    slider15PhaseValue=0;
    slider17PhaseValue=0;
    slider19PhaseValue=0;
    slider22PhaseValue=0;

    slidersPhaseValues.set("phaseSubSlider",&subSliderPhaseValue);
    slidersPhaseValues.set("phaseSlider5",&slider5PhaseValue);
    slidersPhaseValues.set("phaseMainSlider",&mainSliderPhaseValue);
    slidersPhaseValues.set("phaseSlider8",&slider8PhaseValue);
    slidersPhaseValues.set("phaseSlider12",&slider12PhaseValue);
    slidersPhaseValues.set("phaseSlider15",&slider15PhaseValue);
    slidersPhaseValues.set("phaseSlider17",&slider17PhaseValue);
    slidersPhaseValues.set("phaseSlider19",&slider19PhaseValue);
    slidersPhaseValues.set("phaseSlider22",&slider22PhaseValue);
    
    subSliderWaveValue=0;
    slider5WaveValue=0;
    mainSliderWaveValue=0;
    slider8WaveValue=0;
    slider12WaveValue=0;
    slider15WaveValue=0;
    slider17WaveValue=0;
    slider19WaveValue=0;
    slider22WaveValue=0;
   
    slidersWaveValues.set("waveSubSlider",&subSliderWaveValue);
    slidersWaveValues.set("waveSlider5",&slider5WaveValue);
    slidersWaveValues.set("waveMainSlider",&mainSliderWaveValue);
    slidersWaveValues.set("waveSlider8",&slider8WaveValue);
    slidersWaveValues.set("waveSlider12",&slider12WaveValue);
    slidersWaveValues.set("waveSlider15",&slider15WaveValue);
    slidersWaveValues.set("waveSlider17",&slider17WaveValue);
    slidersWaveValues.set("waveSlider19",&slider19WaveValue);
    slidersWaveValues.set("waveSlider22",&slider22WaveValue);

    subSliderTremValue=0;
    slider5TremValue=0;
    mainSliderTremValue=0;
    slider8TremValue=0;
    slider12TremValue=0;
    slider15TremValue=0;
    slider17TremValue=0;
    slider19TremValue=0;
    slider22TremValue=0;
    
    slidersTremValues.set("tremSubSlider",&subSliderTremValue);
    slidersTremValues.set("tremSlider5",&slider5TremValue);
    slidersTremValues.set("tremMainSlider",&mainSliderTremValue);
    slidersTremValues.set("tremSlider8",&slider8TremValue);
    slidersTremValues.set("tremSlider12",&slider12TremValue);
    slidersTremValues.set("tremSlider15",&slider15TremValue);
    slidersTremValues.set("tremSlider17",&slider17TremValue);
    slidersTremValues.set("tremSlider19",&slider19TremValue);
    slidersTremValues.set("tremSlider22",&slider22TremValue);
    
    
}

ToneWheelSineAudioProcessor::~ToneWheelSineAudioProcessor()
{
    delete theWheelGenerator;
}

//==============================================================================
const String ToneWheelSineAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int ToneWheelSineAudioProcessor::getNumParameters()
{
    return 0;
}

float ToneWheelSineAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void ToneWheelSineAudioProcessor::setParameter (int index, float newValue)
{
}

const String ToneWheelSineAudioProcessor::getParameterName (int index)
{
    return String();
}

const String ToneWheelSineAudioProcessor::getParameterText (int index)
{
    return String();
}

void ToneWheelSineAudioProcessor::notifyChangedParameter(String sliderName, float value)
{
    theWheelGenerator->setParameter(sliderName, value);
}

const String ToneWheelSineAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ToneWheelSineAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ToneWheelSineAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ToneWheelSineAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ToneWheelSineAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ToneWheelSineAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ToneWheelSineAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double ToneWheelSineAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ToneWheelSineAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ToneWheelSineAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ToneWheelSineAudioProcessor::setCurrentProgram (int index)
{
}

const String ToneWheelSineAudioProcessor::getProgramName (int index)
{
    return String();
}

void ToneWheelSineAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ToneWheelSineAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	theWheelGenerator->initWheel(
                                 sampleRate,
                                 &slidersValues,
                                 &slidersPhaseValues,
                                 &slidersWaveValues,
                                 &slidersTremValues,
                                 &harmonicStyle,
                                 &tremoloSpeed,
                                 &tremoloDepth);

}

void ToneWheelSineAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void ToneWheelSineAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	const int numSamples = buffer.getNumSamples();
    
    // Call to the generator===============================================
    theWheelGenerator->renderNextBlock(buffer, 0, numSamples, midiMessages);
    
    // Apply Mian Volume ===============================================
    buffer.applyGain(mainVolume);

}

//==============================================================================
bool ToneWheelSineAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ToneWheelSineAudioProcessor::createEditor()
{
    DBG("Createeditor");
    return new ToneWheelSineAudioProcessorEditor (*this);
}


//==============================================================================
void ToneWheelSineAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // Create an outer XML element..
    XmlElement xml ("TWSSettings");
    
    //sore all necessary attributes
    
    //generic attribute
    xml.setAttribute ("mainVolume", mainVolume);
    xml.setAttribute ("harmonicStyle", harmonicStyle);
    xml.setAttribute ("tremoloSpeed", tremoloSpeed);
    xml.setAttribute ("tremoloDepth", tremoloDepth);
    
    //sliders values
    xml.setAttribute ("subSliderValue", subSliderValue);
    xml.setAttribute ("slider5Value", slider5Value);
    xml.setAttribute ("mainSliderValue", mainSliderValue);
    xml.setAttribute ("slider8Value", slider8Value);
    xml.setAttribute ("slider12Value", slider12Value);
    xml.setAttribute ("slider15Value", slider15Value);
    xml.setAttribute ("slider17Value", slider17Value);
    xml.setAttribute ("slider19Value", slider19Value);
    xml.setAttribute ("slider22Value", slider22Value);
    
    //phase sliders values
    xml.setAttribute ("subSliderPhaseValue", subSliderPhaseValue);
    xml.setAttribute ("slider5PhaseValue", slider5PhaseValue);
    xml.setAttribute ("mainSliderPhaseValue", mainSliderPhaseValue);
    xml.setAttribute ("slider8PhaseValue", slider8PhaseValue);
    xml.setAttribute ("slider12PhaseValue", slider12PhaseValue);
    xml.setAttribute ("slider15PhaseValue", slider15PhaseValue);
    xml.setAttribute ("slider17PhaseValue", slider17PhaseValue);
    xml.setAttribute ("slider19PhaseValue", slider19PhaseValue);
    xml.setAttribute ("slider22PhaseValue", slider22PhaseValue);
    
    //wave sliders values
    xml.setAttribute ("subSliderWaveValue", subSliderWaveValue);
    xml.setAttribute ("slider5WaveValue", slider5WaveValue);
    xml.setAttribute ("mainSliderWaveValue", mainSliderWaveValue);
    xml.setAttribute ("slider8WaveValue", slider8WaveValue);
    xml.setAttribute ("slider12WaveValue", slider12WaveValue);
    xml.setAttribute ("slider15WaveValue", slider15WaveValue);
    xml.setAttribute ("slider17WaveValue", slider17WaveValue);
    xml.setAttribute ("slider19WaveValue", slider19WaveValue);
    xml.setAttribute ("slider22WaveValue", slider22WaveValue);
    
    //trem sliders values
    xml.setAttribute ("subSliderTremValue", subSliderTremValue);
    xml.setAttribute ("slider5TremValue", slider5TremValue);
    xml.setAttribute ("mainSliderTremValue", mainSliderTremValue);
    xml.setAttribute ("slider8TremValue", slider8TremValue);
    xml.setAttribute ("slider12TremValue", slider12TremValue);
    xml.setAttribute ("slider15TremValue", slider15TremValue);
    xml.setAttribute ("slider17TremValue", slider17TremValue);
    xml.setAttribute ("slider19TremValue", slider19TremValue);
    xml.setAttribute ("slider22TremValue", slider22TremValue);
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
    
    
}


void ToneWheelSineAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("TWSSettings"))
        {
            // ok, now pull out our parameters..
            //generic attribute
            mainVolume = (float) xmlState->getDoubleAttribute ("mainVolume", mainVolume);
            harmonicStyle = (float) xmlState->getDoubleAttribute ("harmonicStyle", harmonicStyle);
            tremoloSpeed = (float) xmlState->getDoubleAttribute ("tremoloSpeed", tremoloSpeed);
            tremoloDepth = (float) xmlState->getDoubleAttribute ("tremoloDepth", tremoloDepth);
            
            //sliders values
            subSliderValue = (float) xmlState->getDoubleAttribute ("subSliderValue", subSliderValue);
            slider5Value = (float) xmlState->getDoubleAttribute ("slider5Value", slider5Value);
            mainSliderValue = (float) xmlState->getDoubleAttribute ("mainSliderValue", mainSliderValue);
            slider8Value = (float) xmlState->getDoubleAttribute ("slider8Value", slider8Value);
            slider12Value = (float) xmlState->getDoubleAttribute ("slider12Value", slider12Value);
            slider15Value = (float) xmlState->getDoubleAttribute ("slider15Value", slider15Value);
            slider17Value = (float) xmlState->getDoubleAttribute ("slider17Value", slider17Value);
            slider19Value = (float) xmlState->getDoubleAttribute ("slider19Value", slider19Value);
            slider22Value = (float) xmlState->getDoubleAttribute ("slider22Value", slider22Value);
            
            //phase sliders values
            subSliderPhaseValue = (float) xmlState->getDoubleAttribute ("subSliderPhaseValue", subSliderPhaseValue);
            slider5PhaseValue = (float) xmlState->getDoubleAttribute ("slider5PhaseValue", slider5PhaseValue);
            mainSliderPhaseValue = (float) xmlState->getDoubleAttribute ("mainSliderPhaseValue", mainSliderPhaseValue);
            slider8PhaseValue = (float) xmlState->getDoubleAttribute ("slider8PhaseValue", slider8PhaseValue);
            slider12PhaseValue = (float) xmlState->getDoubleAttribute ("slider12PhaseValue", slider12PhaseValue);
            slider15PhaseValue = (float) xmlState->getDoubleAttribute ("slider15PhaseValue", slider15PhaseValue);
            slider17PhaseValue = (float) xmlState->getDoubleAttribute ("slider17PhaseValue", slider17PhaseValue);
            slider19PhaseValue = (float) xmlState->getDoubleAttribute ("slider19PhaseValue", slider19PhaseValue);
            slider22PhaseValue = (float) xmlState->getDoubleAttribute ("slider22PhaseValue", slider22PhaseValue);
            
            //wave sliders values
            subSliderWaveValue = xmlState->getIntAttribute ("subSliderWaveValue", subSliderWaveValue);
            slider5WaveValue = xmlState->getIntAttribute ("slider5WaveValue", slider5WaveValue);
            mainSliderWaveValue = xmlState->getIntAttribute ("mainSliderWaveValue", mainSliderWaveValue);
            slider8WaveValue = xmlState->getIntAttribute ("slider8WaveValue", slider8WaveValue);
            slider12WaveValue = xmlState->getIntAttribute ("slider12WaveValue", slider12WaveValue);
            slider15WaveValue = xmlState->getIntAttribute ("slider15WaveValue", slider15WaveValue);
            slider17WaveValue = xmlState->getIntAttribute ("slider17WaveValue", slider17WaveValue);
            slider19WaveValue = xmlState->getIntAttribute ("slider19WaveValue", slider19WaveValue);
            slider22WaveValue = xmlState->getIntAttribute ("slider22WaveValue", slider22WaveValue);
            
            //trem sliders values
            subSliderTremValue = (float) xmlState->getDoubleAttribute ("subSliderTremValue", subSliderTremValue);
            slider5TremValue = (float) xmlState->getDoubleAttribute ("slider5TremValue", slider5TremValue);
            mainSliderTremValue = (float) xmlState->getDoubleAttribute ("mainSliderTremValue", mainSliderTremValue);
            slider8TremValue = (float) xmlState->getDoubleAttribute ("slider8TremValue", slider8TremValue);
            slider12TremValue = (float) xmlState->getDoubleAttribute ("slider12TremValue", slider12TremValue);
            slider15TremValue = (float) xmlState->getDoubleAttribute ("slider15TremValue", slider15TremValue);
            slider17TremValue = (float) xmlState->getDoubleAttribute ("slider17TremValue", slider17TremValue);
            slider19TremValue = (float) xmlState->getDoubleAttribute ("slider19TremValue", slider19TremValue);
            slider22TremValue = (float) xmlState->getDoubleAttribute ("slider22TremValue", slider22TremValue);
            
            //notify the generator
            theWheelGenerator->initWheel(
                                         0,
                                         &slidersValues,
                                         &slidersPhaseValues,
                                         &slidersWaveValues,
                                         &slidersTremValues,
                                         &harmonicStyle,
                                         &tremoloSpeed,
                                         &tremoloDepth);
            
            //notify the UI
            
            
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ToneWheelSineAudioProcessor();
}






