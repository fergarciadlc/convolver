/*
  ==============================================================================

    Convolution.cpp
    Created: 20 Sep 2022 6:00:08pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Convolution.h"

Convolution::Convolution() {}

Convolution::~Convolution() {}

void Convolution::prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels)
{
    //// load IR file from local wav    
    //juce::File IRFile = FileHandler.getIRFromIRFolder("Conic Long Echo Hall.wav");
    //DBG(IRFile.getFullPathName());

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inNumChannels;

    // start convolution
    conv.reset();
    conv.prepare(spec);

    //// load IR from file
    //conv.loadImpulseResponse(
    //    IRFile.getFullPathName(),
    //    juce::dsp::Convolution::Stereo::yes,
    //    juce::dsp::Convolution::Trim::yes,
    //    IRFile.getSize(),
    //    juce::dsp::Convolution::Normalise::yes
    //);
    conv.loadImpulseResponse(
        BinaryData::conic_long_echo_hall_wav,
        BinaryData::conic_long_echo_hall_wavSize,
        juce::dsp::Convolution::Stereo::yes,
        juce::dsp::Convolution::Trim::yes,
        0, // request original size of IR
        juce::dsp::Convolution::Normalise::yes
      );

}

void Convolution::process(juce::AudioBuffer<float> inBuffer, bool isBypassed)
{
    if (isBypassed) { return; }
    juce::dsp::AudioBlock<float> block(inBuffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    conv.process(context);
}