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

    juce::DrawableButton diode1Switch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> diode1Attachment;

    juce::DrawableButton diode2Switch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> diode2Attachment;

    struct {
        std::unique_ptr<juce::XmlElement> diode_1_open_xml;
        std::unique_ptr<juce::Drawable>   diode_1_open;
        std::unique_ptr<juce::XmlElement> diode_2_open_xml;
        std::unique_ptr<juce::Drawable>   diode_2_open;
        std::unique_ptr<juce::XmlElement> diode_1_closed_xml;
        std::unique_ptr<juce::Drawable>   diode_1_closed;
        std::unique_ptr<juce::XmlElement> diode_2_closed_xml;
        std::unique_ptr<juce::Drawable>   diode_2_closed;

        std::unique_ptr<juce::XmlElement> opAmp_xml;
        std::unique_ptr<juce::Drawable>   opAmp;
    } svg;

    xynth::GuiData& guiData;
};