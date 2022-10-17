/*
  ==============================================================================

    ControlsComponent.h
    Created: 2 Oct 2022 9:56:39pm
    Author:  Fernando Garcia

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Helpers/Parameters.h"
#include "../../PluginProcessor.h"

class ControlsComponent : public juce::Component
{
public:
    ControlsComponent (ConvolverAudioProcessor&);
    ~ControlsComponent() override;
    
    void paint (juce::Graphics&) override;
    
    void resized() override;
    
//    std::vector<juce::Slider*> getSlidersReference() { return sliders; }
    
    using mSliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void createSliderWithAttachment (juce::Slider& sliderObj,
                                     std::unique_ptr<mSliderAttachment>& sliderAttach,
                                     juce::String paramID,
                                     juce::Label& labelObj,
                                     juce::String labelStr);
private:
    
    ConvolverAudioProcessor& audioProcessor;
    
    juce::Slider inputSlider;
    juce::Slider outputSlider;
    juce::Slider mixSlider;
    
//    using sliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<mSliderAttachment> inputAttach;
    std::unique_ptr<mSliderAttachment> outputAttach;
    std::unique_ptr<mSliderAttachment> mixAttach;
    
//    std::vector<juce::Slider*> sliders { &inputSlider, &outputSlider, &mixSlider };
    
    juce::Label inputLabel;
    juce::Label outputLabel;
    juce::Label mixLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)

};
