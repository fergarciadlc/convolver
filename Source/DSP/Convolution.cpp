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

void Convolution::prepare (juce::dsp::ProcessSpec spec)
{
    conv.reset();
    conv.prepare(spec);
}

void Convolution::updateIR (juce::String irFilePath)
{
    irFile = juce::File(irFilePath);
    if (! irFile.existsAsFile())
    {
        DBG("File does not exists");
        DBG(irFilePath);
        isBypassed = true;
        return;  // file does nott exist
    }
    
    conv.loadImpulseResponse(irFile.getFullPathName(),
                             juce::dsp::Convolution::Stereo::yes,
                             juce::dsp::Convolution::Trim::yes,
                             irFile.getSize(),
                             juce::dsp::Convolution::Normalise::yes);

}


void Convolution::process (juce::AudioBuffer<float>& inBuffer)
{
    if (isBypassed)
        return;
    juce::dsp::AudioBlock<float> block(inBuffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    conv.process(context);
}
