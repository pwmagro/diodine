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

    mixSlider.slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mixSlider.init(g.audioProcessor.treeState, MIX_ID);
    addAndMakeVisible(mixSlider.slider);
    mixSlider.slider.onValueChange = [this]() { repaint(); };

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
    const int spacing = 5;
    guiData.getLnf().drawMainBackground(g, rect);
    
    g.setColour(guiData.getLnf().getTextColor().darker(1.2f).withAlpha(0.7f));
    auto topRect = rect.removeFromTop(rect.getHeight() / 3.f);
    g.drawHorizontalLine(topRect.getBottom(), topRect.getX() + 20, topRect.getRight() - 20);
    auto topLeftRect = topRect.removeFromLeft(300.f);
    g.drawVerticalLine(topLeftRect.getRight(), topLeftRect.getY() + 20, topLeftRect.getBottom() - 20);
    logo.setBounds(topLeftRect.removeFromTop(100.f).reduced(spacing, spacing));
    g.drawHorizontalLine(topLeftRect.getY(), topLeftRect.getX() + 20, topLeftRect.getRight() - 20);
    oscilloscopeDisplay.setBounds(topLeftRect.reduced(spacing, spacing));

    auto mixRect = topRect.removeFromRight(60.f).reduced(10, 0);
    g.drawVerticalLine(topRect.getRight(), topRect.getY() + 20, topRect.getBottom() - 20);

    g.setColour(guiData.getLnf().getFgColor());
    g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(20));
    g.drawText("dry", mixRect.removeFromBottom(25), juce::Justification::centredTop);
    g.drawText("wet", mixRect.removeFromTop(25), juce::Justification::centredBottom);
    mixSlider.slider.setBounds(mixRect.toNearestInt());
    
    circuitDisplay.setBounds(topRect.reduced(spacing, spacing));


    if (logo.getButtonState()) {
        voltageDisplay.setVisible(false);
        timingDisplay.setVisible(false);

        g.setColour(guiData.getLnf().getFgColor());
        g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(30));
        g.drawText("diodine by wdym", rect.translated(0, -35), juce::Justification::centred, false);
        g.setFont(20);
        g.drawText("special thanks to Speechrezz of Xynth Audio", rect, juce::Justification::centred, false);

        hue.setVisible(true);
        hue.setBounds(rect.removeFromBottom(80).withTrimmedBottom(15));
    }
    else {
        hue.setVisible(false);
        voltageDisplay.setVisible(true);
        timingDisplay.setVisible(true);
        voltageDisplay.setBounds(rect.removeFromLeft(rect.getWidth() / 2.f).reduced(spacing, spacing));
        timingDisplay.setBounds(rect.reduced(spacing, spacing));
    }
}

void WindowLayout::resized()
{
    const int spacing = 5;

    auto rect = getLocalBounds();
    rect.reduce(spacing, spacing);
}
