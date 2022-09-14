/*
  ==============================================================================

    TimingGraph.h
    Created: 11 Sep 2022 8:26:23pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"


class TimingGraph : public juce::Component, juce::Timer {
public:
    void timerCallback() override;
};