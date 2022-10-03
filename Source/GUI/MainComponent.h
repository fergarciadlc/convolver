/*
  ==============================================================================

    MainComponent.h
    Created: 2 Oct 2022 9:18:17pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "Controls/ControlsComponent.h"

static const int MAIN_WIDTH = 700;
static const int MAIN_HEIGHT = 450;

class MainComponent : public juce::Component
{
public:
    
    MainComponent (ConvolverAudioProcessor&);
    
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    
    void resized() override;
    

private:

    ConvolverAudioProcessor& audioProcessor;
    ControlsComponent controlsComponent { audioProcessor };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
