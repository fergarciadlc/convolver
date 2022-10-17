/*
  ==============================================================================

    ControlsComponent.cpp
    Created: 2 Oct 2022 9:56:39pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#include "ControlsComponent.h"


void ControlsComponent::createSliderWithAttachment (juce::Slider& sliderObj,
                                                    std::unique_ptr<mSliderAttachment>& sliderAttach,
                                                    juce::String paramID,
                                                    juce::Label& labelObj,
                                                    juce::String labelStr)
{
    addAndMakeVisible (sliderObj);
    sliderObj.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderObj.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    
    sliderAttach = std::make_unique<mSliderAttachment> (audioProcessor.apvts, paramID, sliderObj);
    
    labelObj.setText (labelStr, juce::dontSendNotification);
    labelObj.setJustificationType (juce::Justification::centred);
    labelObj.attachToComponent (&sliderObj, false);
    addAndMakeVisible (labelObj);
}

ControlsComponent::ControlsComponent (ConvolverAudioProcessor& p) : audioProcessor (p)
{
    createSliderWithAttachment (inputSlider, inputAttach, INPUT_PARAM, inputLabel, INPUT_PARAM);
    createSliderWithAttachment (outputSlider, outputAttach, OUTPUT_PARAM, outputLabel, OUTPUT_PARAM);
    createSliderWithAttachment (mixSlider, mixAttach, MIX_PARAM, mixLabel, MIX_PARAM);
}

ControlsComponent::~ControlsComponent() {}

void ControlsComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkcyan);
}

void ControlsComponent::resized()
{
    inputSlider     .setBoundsRelative (0.00f, 0.25f, 0.33f, 0.7f);
    mixSlider       .setBoundsRelative (0.33f, 0.25f, 0.33f, 0.7f);
    outputSlider    .setBoundsRelative (0.66f, 0.25f, 0.33f, 0.7f);
}
