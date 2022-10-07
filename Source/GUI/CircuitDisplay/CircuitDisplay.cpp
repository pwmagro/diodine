/*
  ==============================================================================

    CircuitDisplay.cpp
    Created: 11 Sep 2022 8:26:55pm
    Author:  pwmag

  ==============================================================================
*/

#include "CircuitDisplay.h"

CircuitDisplay::CircuitDisplay(xynth::GuiData& g) : guiData(g)
{
    diode1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(g.audioProcessor.treeState, DIODE_1_ID, diode1Switch);
    diode2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(g.audioProcessor.treeState, DIODE_2_ID, diode2Switch);

    gainSlider.init(g.audioProcessor.treeState, GAIN_ID);
    mixSlider.init(g.audioProcessor.treeState, MIX_ID);

    addAndMakeVisible(diode1Switch);
    addAndMakeVisible(diode2Switch);
    addAndMakeVisible(gainSlider.slider);
    addAndMakeVisible(gainSlider.slider);
}

void CircuitDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds().toFloat();
    rect.reduce(10, 10);
    auto oneQuarter = rect.proportionOfWidth(0.25f);
    auto& lnf = guiData.getLnf();

    auto leftRect = rect.removeFromLeft(oneQuarter);
    auto topLeftRect = leftRect.removeFromTop(leftRect.getHeight() / 2.f);

    drawOpAmp(g, topLeftRect);
    // draw gain stuff

    auto swRect = rect.removeFromLeft(oneQuarter);
    auto swTopRect = swRect.removeFromTop(swRect.getHeight() / 2.f);

    drawSwitch(g, swTopRect, false);
    drawSwitch(g, swRect, true);

    auto diodeRect = rect.removeFromLeft(oneQuarter);
    auto diodeTopRect = diodeRect.removeFromTop(diodeRect.getHeight() / 2.f);

    drawDiode(g, diodeTopRect, false);
    drawDiode(g, diodeRect, true);

#ifdef JUCE_DEBUG
    // Ensure that rect has been scaled appropriately
    g.setColour(guiData.getLnf().getTextColor().darker(2));
    g.fillRect(rect);
#endif
}

void CircuitDisplay::drawDiode(juce::Graphics& g, juce::Rectangle<float> bounds, bool facingLeft) {
    const float offset = 20;
    auto center = bounds.getCentre();

    juce::Path diode;

    if (!facingLeft) {
        // triangle
        diode.startNewSubPath(center.getX() - offset, center.getY() - offset);
        diode.lineTo(center.getX() + offset, center.getY());
        diode.lineTo(center.getX() - offset, center.getY() + offset);
        diode.closeSubPath();

        // line
        diode.startNewSubPath(center.getX() + offset, center.getY() - offset);
        diode.lineTo(center.getX() + offset, center.getY() + offset);
    }
    else {
        // triangle
        diode.startNewSubPath(center.getX() + offset, center.getY() - offset);
        diode.lineTo(center.getX() - offset, center.getY());
        diode.lineTo(center.getX() + offset, center.getY() + offset);
        diode.closeSubPath();

        // line
        diode.startNewSubPath(center.getX() - offset, center.getY() - offset);
        diode.lineTo(center.getX() - offset, center.getY() + offset);
    }

    diode.startNewSubPath(bounds.getX(), center.getY());
    diode.lineTo(center.getX() - offset, center.getY());

    diode.startNewSubPath(center.getX() + offset, center.getY());
    diode.lineTo(bounds.getRight(), center.getY());

    g.setColour(guiData.getLnf().getFgColor());
    g.strokePath(diode, juce::PathStrokeType(4.f));
}

void CircuitDisplay::drawSwitch(juce::Graphics& g, juce::Rectangle<float> bounds, bool isOpen) {
    const float offset = 30;
    auto center = bounds.getCentre();

    juce::Path sw;

    sw.startNewSubPath(bounds.getX(), center.getY());
    sw.lineTo(center.getX() - offset, center.getY());

    sw.addEllipse(center.getX() - offset, center.getY() - 4, 8, 8);

    sw.startNewSubPath(center.getX() - offset + 8, center.getY());

    if (isOpen) {
        sw.lineTo(center.getX() + offset - 8, center.getY() - (offset / 2.f));
    }
    else {
        sw.lineTo(center.getX() + offset - 8, center.getY());
    }

    sw.addEllipse(center.getX() + offset - 8, center.getY() - 4, 8, 8);

    sw.startNewSubPath(center.getX() + offset, center.getY());
    sw.lineTo(bounds.getRight(), center.getY());

    g.setColour(guiData.getLnf().getFgColor());
    g.strokePath(sw, juce::PathStrokeType(4.f));
}

void CircuitDisplay::drawOpAmp(juce::Graphics& g, juce::Rectangle<float> bounds) {
    const float offset = 30;
    auto center = bounds.getCentre();

    juce::Path opAmp;
    opAmp.startNewSubPath(center.getX() - offset, center.getY() - offset);
    opAmp.lineTo(center.getX() + offset, center.getY());
    opAmp.lineTo(center.getX() - offset, center.getY() + offset);
    opAmp.closeSubPath();

    opAmp.startNewSubPath(bounds.getX(), center.getY() - (offset / 2.f));
    opAmp.lineTo(center.getX() - offset, center.getY() - (offset / 2.f));
    opAmp.startNewSubPath(center.getX() - offset, center.getY() + (offset / 2.f));
    opAmp.lineTo(bounds.getX(), center.getY() + (offset / 2.f));
    opAmp.lineTo(bounds.getX(), bounds.getBottom());

    opAmp.startNewSubPath(bounds.getRight(), center.getY());
    opAmp.lineTo(center.getX() + offset, center.getY());

    g.setColour(guiData.getLnf().getFgColor());
    g.strokePath(opAmp, juce::PathStrokeType(4.f));
}