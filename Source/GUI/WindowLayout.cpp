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
                                                voltageDisplay(g), timingDisplay(g), logo(g), hue(g),
                                                oscilloscopeDisplay(g, guiData.audioProcessor.getRingBufferRef())
{
    auto& treeState = g.audioProcessor.treeState;

    // Add and make visible
    addAndMakeVisible(circuitDisplay);
    addAndMakeVisible(oscilloscopeDisplay);
    addAndMakeVisible(voltageDisplay);
    addAndMakeVisible(timingDisplay);
    addAndMakeVisible(logo);
    addAndMakeVisible(hue);
    addChildComponent(aboutOverlay);

    guiData.showAbout = [this]() { aboutOverlay.setVisible(true); };
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::paint (juce::Graphics& g)
{
    auto rect = getLocalBounds();
    const int spacing = 2;


    g.setColour(guiData.getLnf().getOutlineColor());
    g.fillRect(rect);

    auto topRect = rect.removeFromTop(rect.getHeight() / 3.f);
    auto topLeftRect = topRect.removeFromLeft(300.f);
    logo.setBounds(topLeftRect.removeFromTop(100.f).reduced(spacing, spacing));
    oscilloscopeDisplay.setBounds(topLeftRect.removeFromLeft(200.f).reduced(spacing, spacing));
    hue.setBounds(topLeftRect.reduced(spacing, spacing));
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
