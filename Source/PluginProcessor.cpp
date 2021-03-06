/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "MainComponent.h"


//==============================================================================
RayAudioProcessor::RayAudioProcessor()
{
    this->parameters.add(new teragon::BooleanParameter("Awesomeness", true));
    this->parameters.add(new teragon::FrequencyParameter("Frequency", 20.0, 20000.0, 10000.0));
    this->parameters.add(new teragon::DecibelParameter("Gain", -60.0, 3.0, 0.0));
}

RayAudioProcessor::~RayAudioProcessor()
{
}

//==============================================================================
const String RayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int RayAudioProcessor::getNumParameters()
{
    return 0;
}

float RayAudioProcessor::getParameter (int index)
{
    return this->parameters[index]->getScaledValue();
}

void RayAudioProcessor::setParameter (int index, float newValue)
{
    this->parameters.setScaled(index, newValue);
}

const String RayAudioProcessor::getParameterName (int index)
{
    return this->parameters[index]->getName();
}

const String RayAudioProcessor::getParameterText (int index)
{
    return this->parameters[index]->getDisplayText();
}

const String RayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String RayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool RayAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool RayAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool RayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double RayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RayAudioProcessor::setCurrentProgram (int index)
{
}

const String RayAudioProcessor::getProgramName (int index)
{
    return String();
}

void RayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void RayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    this->parameters.resume();
}

void RayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    this->parameters.pause();
}

void RayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    this->parameters.processRealtimeEvents();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool RayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RayAudioProcessor::createEditor()
{
    return new MainComponent (*this, parameters, Resources::getCache());
}

//==============================================================================
void RayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RayAudioProcessor();
}
