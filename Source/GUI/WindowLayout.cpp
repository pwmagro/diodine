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
                                                voltageDisplay(g), timingDisplay(g), logo(g),
                                                oscilloscopeDisplay(g)
{
    auto& treeState = g.audioProcessor.treeState;

    // Add and make visible
    addAndMakeVisible(circuitDisplay);
    addAndMakeVisible(oscilloscopeDisplay);
    addAndMakeVisible(voltageDisplay);
    addAndMakeVisible(timingDisplay);
    addAndMakeVisible(logo);
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


    g.setColour(WDYM::OutlineColor);
    g.fillRect(rect);

    auto topRect = rect.removeFromTop(HEIGHT / 3.f);
    circuitDisplay.setBounds(topRect.removeFromRight(WIDTH * 2.f / 3.f).reduced(spacing, spacing));
    logo.setBounds(topRect.removeFromTop(topRect.getHeight() / 2.f).reduced(spacing, spacing));
    oscilloscopeDisplay.setBounds(topRect.reduced(spacing, spacing));
    voltageDisplay.setBounds(rect.removeFromLeft(WIDTH / 2.f).reduced(spacing, spacing));
    timingDisplay.setBounds(rect.reduced(spacing, spacing));
}

void WindowLayout::resized()
{
    const int spacing = 5;

    auto rect = getLocalBounds();
    rect.reduce(spacing, spacing);

    
}
