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
#include "../Utils/FullSlider.h"

#include "SwitchButton.h"

class CircuitDisplay : public juce::Component {
public:
    CircuitDisplay(xynth::GuiData& g);
    void paint(juce::Graphics& g);

private:
    xynth::FullSlider gainSlider;
    xynth::FullSlider mixSlider;

    SwitchButton diode1Switch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> diode1Attachment;

    SwitchButton diode2Switch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> diode2Attachment;

    xynth::GuiData& guiData;

    void drawDiode(juce::Graphics& g, juce::Rectangle<float> bounds, bool facingLeft = false);
    void drawSwitch(juce::Graphics& g, juce::Rectangle<float> bounds, bool isOpen);
    void drawOpAmp(juce::Graphics& g, juce::Rectangle<float> bounds);
};