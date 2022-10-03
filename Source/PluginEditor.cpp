/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolverAudioProcessorEditor::ConvolverAudioProcessorEditor (ConvolverAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (MAIN_WIDTH, MAIN_HEIGHT);
    addAndMakeVisible(mainComponent);
    setResizable(false, false);
}

ConvolverAudioProcessorEditor::~ConvolverAudioProcessorEditor()
{
}

//==============================================================================
void ConvolverAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void ConvolverAudioProcessorEditor::resized()
{
    mainComponent.setTopLeftPosition(0, 0);
}
