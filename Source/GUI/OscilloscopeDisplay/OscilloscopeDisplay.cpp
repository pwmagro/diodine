/*
  ==============================================================================

    OscilloscopeDisplay.cpp
    Created: 12 Sep 2022 6:48:51pm
    Author:  pwmag

  ==============================================================================
*/

#include "OscilloscopeDisplay.h"

OscilloscopeDisplay::OscilloscopeDisplay(xynth::GuiData& g, xynth::RingBuffer* r) : guiData(g) {
    startTimerHz(60);
    
}

void OscilloscopeDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);
    rect.reduce(25.f, 25.f);
    //guiData.getLnf().drawGraphBackground(g, rect.toFloat(), 1);

    auto& fixedBuffer = guiData.audioProcessor.fixedBuffer;
    const auto oscLength = fixedBuffer.getWidth();

    juce::Path line;
    line.clear();
    line.startNewSubPath(rect.getX(), rect.getCentreY() - fixedBuffer.getSample(0) * 0.5 * rect.getHeight());
    for (int i = 1; i < oscLength; i += 10) {
        line.lineTo(rect.getX() + i * rect.getWidth() / oscLength, rect.getCentreY() - fixedBuffer.getSample(i) * 0.5 * rect.getHeight());
    }

    g.setColour(guiData.getLnf().getTextColor().withSaturation(1.f));
    g.strokePath(line, juce::PathStrokeType(1.f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));
}

void OscilloscopeDisplay::timerCallback() {
    repaint();
}