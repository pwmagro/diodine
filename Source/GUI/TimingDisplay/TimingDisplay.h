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

class TimingDisplay : public juce::Component {
public:
    TimingDisplay(xynth::GuiData& g);
    void paint(juce::Graphics& g);
private:
    juce::Slider trrSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trrAttach;
    
    //TimingGraph timingGraph;

    xynth::GuiData& guiData;
};