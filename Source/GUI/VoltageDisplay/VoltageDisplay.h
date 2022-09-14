/*
  ==============================================================================

    VoltageDisplay.h
    Created: 11 Sep 2022 8:39:10pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

#include "VdSlider.h"
#include "VfSlider.h"
#include "VoltageGraph.h"

class VoltageDisplay : public juce::Component {
public:
    VoltageDisplay(xynth::GuiData& g);
    void paint(juce::Graphics& g);
private:
    juce::Slider vbSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vbAttach;

    juce::Slider vfSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> vfAttach;

    juce::Slider satSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> satAttach;
    //VoltageGraph voltageGraph;

    xynth::GuiData& guiData;
};