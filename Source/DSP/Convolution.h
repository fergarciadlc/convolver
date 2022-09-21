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

    void prepare (juce::dsp::ProcessSpec spec);
    
    void updateIR (juce::String irFilePath);

    void process (juce::AudioBuffer<float>& inBuffer);

    bool isBypassed { false };
    
private:
    juce::dsp::Convolution conv;
    juce::File irFile;
    
};
