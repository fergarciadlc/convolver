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
    
    void setIR (juce::String irFilePath);
    
    void setBypass (bool bypass);

    void process (juce::AudioBuffer<float>& inBuffer);

    
private:
    juce::dsp::Convolution conv;
    juce::File irFile;
    bool isBypassed { false };
    
};
