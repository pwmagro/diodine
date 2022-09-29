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
#include "../../Common/RingBuffer.h"

class OscilloscopeDisplay : public juce::Component, juce::Timer {
public:
    OscilloscopeDisplay(xynth::GuiData& g, xynth::RingBuffer* r);
    void paint(juce::Graphics& g);

private:
    xynth::GuiData& guiData;

    void timerCallback() override;
};


class A {
public:
    A();
    ~A();

};