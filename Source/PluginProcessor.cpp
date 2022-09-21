/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolverAudioProcessor::ConvolverAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
}

ConvolverAudioProcessor::~ConvolverAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ConvolverAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("input", 1), "input", 0.0f, 2.0f, 1.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("output", 1), "output", 0.0f, 2.0f, 1.0f));
    params.add(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("bypass", 1), "bypass", false));
    
    return params;
}

//==============================================================================
const juce::String ConvolverAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ConvolverAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ConvolverAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ConvolverAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ConvolverAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ConvolverAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ConvolverAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ConvolverAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ConvolverAudioProcessor::getProgramName (int index)
{
    return {};
}

void ConvolverAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ConvolverAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    convolution.prepare(spec);
}

void ConvolverAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ConvolverAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ConvolverAudioProcessor::updateParameters()
{
    juce::String irFilePath = juce::String ("/Users/fernando/Documents/Library/Media/ImpulseResponses/KalthallenCabsIR/Kalthallen IRs/001a-SM57-V30-4x12.wav");
    float inGainValue = apvts.getRawParameterValue ("input") -> load();
    float outGainValue = apvts.getRawParameterValue ("output") -> load();
    
    convolution.setBypass (apvts.getRawParameterValue ("bypass") -> load());
    convolution.setIR (irFilePath);
    inputGain.updateGain (inGainValue);
    outputGain.updateGain (outGainValue);
}

void ConvolverAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    updateParameters();
    inputGain.process (buffer);
    convolution.process (buffer);
    outputGain.process (buffer);
}

//==============================================================================
bool ConvolverAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ConvolverAudioProcessor::createEditor()
{
//    return new ConvolverAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void ConvolverAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ConvolverAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvolverAudioProcessor();
}
