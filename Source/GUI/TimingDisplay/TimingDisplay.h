/*
  ==============================================================================

    TimingDisplay.h
    Created: 11 Sep 2022 8:26:03pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

#include "TimingGraph.h"

class TimingDisplay : public juce::Component, juce::Timer {
public:
    TimingDisplay(xynth::GuiData& g);
    void paint(juce::Graphics& g);
private:
    void timerCallback() override { repaint(); }

    juce::Slider trrSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trrAttach;
    
    const int len = 100;

    xynth::GuiData& guiData;
};