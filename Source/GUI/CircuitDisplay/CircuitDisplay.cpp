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

    auto stateChange = [this]() { repaint(); };

    diode1Switch.onStateChange = stateChange;
    diode2Switch.onStateChange = stateChange;
    gainSlider.slider.onValueChange = stateChange;

    addAndMakeVisible(diode1Switch);
    addAndMakeVisible(diode2Switch);
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

    juce::Path connections;
    connections.startNewSubPath(topLeftRect.getX(), topLeftRect.getCentreY() + 15);
    connections.lineTo(leftRect.getX(), leftRect.getCentreY());
    connections.lineTo(leftRect.getRight(), leftRect.getCentreY());
    connections.lineTo(leftRect.getRight(), topLeftRect.getCentreY());

    gainSlider.slider.setBounds(juce::Rectangle<int>(50, 50).withCentre(leftRect.getCentre().roundToInt()));

    g.setFont(lnf.getCustomFontRegular().withHeight(20));
    g.drawText(juce::String(GAIN_NAME).toLowerCase(), leftRect.removeFromBottom(leftRect.getHeight() / 2.f - 25), juce::Justification::centred);

    auto swRect = rect.removeFromLeft(oneQuarter);
    auto swTopRect = swRect.removeFromTop(swRect.getHeight() / 2.f);

    diode1Switch.setBounds(swTopRect.toNearestInt());
    diode2Switch.setBounds(swRect.toNearestInt());

    drawSwitch(g, swTopRect, diode1Switch.getToggleState());
    drawSwitch(g, swRect, diode2Switch.getToggleState());

    auto diodeRect = rect.removeFromLeft(oneQuarter);
    auto diodeTopRect = diodeRect.removeFromTop(diodeRect.getHeight() / 2.f);

    drawDiode(g, diodeTopRect, false);
    drawDiode(g, diodeRect, true);

    connections.startNewSubPath(diodeRect.getRight() - 2, diodeRect.getCentreY());
    connections.lineTo(diodeTopRect.getRight() - 2, diodeTopRect.getCentreY() + 1);
    connections.startNewSubPath(diodeTopRect.getRight() - 2, diodeTopRect.getCentreY());
    connections.lineTo(rect.getRight() - 15, diodeTopRect.getCentreY());

    connections.addEllipse(rect.getRight() - 15, diodeTopRect.getCentreY() - 4, 8, 8);

    connections.startNewSubPath(rect.getRight() - 15, diodeRect.getCentreY() - 12);
    connections.lineTo(rect.getRight() - 15, diodeRect.getCentreY());

    connections.startNewSubPath(rect.getRight() - 30, diodeRect.getCentreY());
    connections.lineTo(rect.getRight(), diodeRect.getCentreY());

    connections.startNewSubPath(rect.getRight() - 23, diodeRect.getCentreY() + 8);
    connections.lineTo(rect.getRight() - 7, diodeRect.getCentreY() + 8);

    connections.startNewSubPath(rect.getRight() - 18, diodeRect.getCentreY() + 16);
    connections.lineTo(rect.getRight() - 12, diodeRect.getCentreY() + 16);


    g.setColour(guiData.getLnf().getFgColor());
    g.strokePath(connections, juce::PathStrokeType(2.5f));

#ifdef JUCE_DEBUG
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
    g.strokePath(diode, juce::PathStrokeType(2.5f));
}

void CircuitDisplay::drawSwitch(juce::Graphics& g, juce::Rectangle<float> bounds, bool isClosed) {
    const float offset = 30;
    auto center = bounds.getCentre();

    juce::Path sw;

    sw.startNewSubPath(bounds.getX(), center.getY());
    sw.lineTo(center.getX() - offset, center.getY());

    sw.addEllipse(center.getX() - offset, center.getY() - 4, 8, 8);

    sw.startNewSubPath(center.getX() - offset + 8, center.getY());

    if (isClosed) {
        sw.lineTo(center.getX() + offset - 8, center.getY());
    }
    else {
        sw.lineTo(center.getX() + offset - 12, center.getY() - (offset * 0.65f));
    }

    sw.addEllipse(center.getX() + offset - 8, center.getY() - 4, 8, 8);

    sw.startNewSubPath(center.getX() + offset, center.getY());
    sw.lineTo(bounds.getRight(), center.getY());

    g.setColour(guiData.getLnf().getFgColor());
    g.strokePath(sw, juce::PathStrokeType(2.5f));
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
    g.strokePath(opAmp, juce::PathStrokeType(2.5f));
}