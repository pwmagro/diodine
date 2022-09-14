/*
  ==============================================================================

    OscilloscopeDisplay.h
    Created: 12 Sep 2022 6:48:51pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class OscilloscopeDisplay : public juce::Component {
public:
    OscilloscopeDisplay(xynth::GuiData& g);
    void paint(juce::Graphics& g);

private:
    //GainSlider gainSlider;
    //MixSlider mixSlider;
    //SwitchButton diode1Switch;
    //SwitchButton diode2Switch;

    xynth::GuiData& guiData;
};