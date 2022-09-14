/*
  ==============================================================================

    OscilloscopeDisplay.cpp
    Created: 12 Sep 2022 6:48:51pm
    Author:  pwmag

  ==============================================================================
*/

#include "OscilloscopeDisplay.h"

OscilloscopeDisplay::OscilloscopeDisplay(xynth::GuiData& g) : guiData(g) {
}

void OscilloscopeDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);

    g.setColour(guiData.getLnf().getAccent1());
    g.setFont(guiData.getLnf().getCustomFontBold().withHeight(45));
    g.drawText("oscilloscope", rect, juce::Justification::centred);
}