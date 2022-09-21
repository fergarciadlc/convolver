/*
  ==============================================================================

    Gain.cpp
    Created: 20 Sep 2022 9:50:31pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain() {}

Gain::~Gain() {}

void Gain::updateGain(float gain)
{
    gainValue = gain;
}

void Gain::process(juce::AudioBuffer<float>& inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float sample = inBuffer.getSample(channel, i);
            inBuffer.setSample(channel, i, gainValue * sample);
        }
    }
}
