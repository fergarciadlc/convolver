/*
  ==============================================================================

    MainComponent.cpp
    Created: 2 Oct 2022 9:18:17pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "./MainComponent.h"

MainComponent::MainComponent (ConvolverAudioProcessor& p) : audioProcessor (p)
{
    addAndMakeVisible (controlsComponent);
    setSize (MAIN_WIDTH, MAIN_HEIGHT);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.drawFittedText ("Convolver", getLocalBounds(), juce::Justification::centred, 1);
}

void MainComponent::resized()
{
//    delayComponent.setBoundsRelative            (0.0f, 0.75f, 0.33f, 0.25f);
    controlsComponent.setBoundsRelative (0.0f, 0.0f, 1.0f, 0.33f);
}
