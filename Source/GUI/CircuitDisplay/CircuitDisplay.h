/*
  ==============================================================================

    CircuitDisplay.h
    Created: 11 Sep 2022 8:26:55pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

#include "GainSlider.h"
#include "MixSlider.h"
#include "SwitchButton.h"

class CircuitDisplay : public juce::Component {
public:
    CircuitDisplay(xynth::GuiData& g);
    void paint(juce::Graphics& g);

private:
    //GainSlider gainSlider;
    //MixSlider mixSlider;
    //SwitchButton diode1Switch;
    //SwitchButton diode2Switch;

    xynth::GuiData& guiData;
};