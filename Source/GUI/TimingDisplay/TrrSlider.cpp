/*
  ==============================================================================

    TrrSlider.cpp
    Created: 11 Sep 2022 8:26:34pm
    Author:  pwmag

  ==============================================================================
*/

#include "TrrSlider.h"
TrrSlider::TrrSlider()
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    slider.setTextBoxIsEditable(true);
}

void TrrSlider::init(juce::AudioProcessorValueTreeState& treeState, juce::String paramID)
{
    attach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, paramID, slider);
}