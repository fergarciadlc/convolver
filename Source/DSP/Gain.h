/*
  ==============================================================================

    Gain.h
    Created: 20 Sep 2022 9:50:31pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Gain
{
public:
    Gain();
    ~Gain();
    
    void updateGain (float gain);
    
    void process (juce::AudioBuffer<float>& inBuffer);
    
    
private:
    float gainValue { 1.0f };
};
