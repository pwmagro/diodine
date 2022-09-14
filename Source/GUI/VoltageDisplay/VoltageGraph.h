/*
  ==============================================================================

    VoltageGraph.h
    Created: 11 Sep 2022 8:46:49pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class VoltageGraph : public juce::Component {
public:
    VoltageGraph(xynth::GuiData& g);
};