/*
  ==============================================================================

    WindowLayout.cpp
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WindowLayout.h"

WindowLayout::WindowLayout(xynth::GuiData& g) : guiData(g), aboutOverlay(g), circuitDisplay(g),
                                                voltageDisplay(g), timingDisplay(g), logo(g), /*hue(g),*/
                                                oscilloscopeDisplay(g, guiData.audioProcessor.getRingBufferRef())
{
    auto& treeState = g.audioProcessor.treeState;

    // Add and make visible
    addAndMakeVisible(circuitDisplay);
    addAndMakeVisible(oscilloscopeDisplay);
    addAndMakeVisible(voltageDisplay);
    addAndMakeVisible(timingDisplay);
    addAndMakeVisible(logo);
    //addAndMakeVisible(hue);
    addChildComponent(aboutOverlay);

    guiData.showAbout = [this]() { aboutOverlay.setVisible(true); };
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    const int spacing = 5;

    guiData.getLnf().drawBackgroundGradient(g, rect, 45, guiData.getLnf().getOutlineColor().brighter(0.05), guiData.getLnf().getOutlineColor().darker(1));

    g.setColour(guiData.getLnf().getFgColor());
    auto topRect = rect.removeFromTop(rect.getHeight() / 3.f);
    g.drawHorizontalLine(topRect.getBottom(), topRect.getX() + 20, topRect.getRight() - 20);
    auto topLeftRect = topRect.removeFromLeft(300.f);
    g.drawVerticalLine(topLeftRect.getRight(), topLeftRect.getY() + 20, topLeftRect.getBottom() - 20);
    logo.setBounds(topLeftRect.removeFromTop(100.f).reduced(spacing, spacing));
    g.drawHorizontalLine(topLeftRect.getY(), topLeftRect.getX() + 20, topLeftRect.getRight() - 20);
    oscilloscopeDisplay.setBounds(topLeftRect.reduced(spacing, spacing));
    //hue.setBounds(topLeftRect.reduced(spacing, spacing));
    circuitDisplay.setBounds(topRect.reduced(spacing, spacing));
    voltageDisplay.setBounds(rect.removeFromLeft(rect.getWidth() / 2.f).reduced(spacing, spacing));
    timingDisplay.setBounds(rect.reduced(spacing, spacing));
}

void WindowLayout::resized()
{
    const int spacing = 5;

    auto rect = getLocalBounds();
    rect.reduce(spacing, spacing);
}
