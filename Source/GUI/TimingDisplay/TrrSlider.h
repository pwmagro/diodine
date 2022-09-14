/*
  ==============================================================================

    TrrSlider.h
    Created: 11 Sep 2022 8:26:34pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

#include "../Utils/FullSlider.h"

class TrrSlider {
public:
    TrrSlider();
    ~TrrSlider() = default;

    void init(juce::AudioProcessorValueTreeState& treeState, juce::String paramID);

    juce::Slider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attach;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrrSlider)
};