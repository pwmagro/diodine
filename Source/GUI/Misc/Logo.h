/*
  ==============================================================================

    Logo.h
    Created: 11 Sep 2022 8:25:12pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

class Logo : public juce::ImageComponent {
public:
    Logo(xynth::GuiData& g);

    void paint(juce::Graphics& g);
    bool getButtonState();

private:
    xynth::GuiData& guiData;
    std::unique_ptr<juce::XmlElement> logo_xml;
    std::unique_ptr<juce::Drawable> logo_svg;
    std::unique_ptr<juce::Drawable> logo_en_svg;

    juce::DrawableButton button;
};