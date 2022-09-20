/*
  ==============================================================================

    Convolution.h
    Created: 20 Sep 2022 6:00:08pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:

    Convolution();
    ~Convolution();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels);

    void process(juce::AudioBuffer<float> inBuffer, bool isBypassed);

private:
    juce::dsp::Convolution conv;
    juce::File IRFile;

};