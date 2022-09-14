/*
  ==============================================================================

    Logo.cpp
    Created: 11 Sep 2022 8:25:12pm
    Author:  pwmag

  ==============================================================================
*/

#include "Logo.h"

Logo::Logo(xynth::GuiData& g) : guiData(g) {
    logo_xml = juce::parseXML(BinaryData::diodine_logo_svg);
    logo_svg = juce::Drawable::createFromSVG(*logo_xml);
}

void Logo::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);
    logo_svg->drawWithin(g, rect.toFloat().reduced(12, 12), juce::RectanglePlacement::centred, 1.f);
    logo_svg->replaceColour(juce::Colours::black, WDYM::FgColor);

}