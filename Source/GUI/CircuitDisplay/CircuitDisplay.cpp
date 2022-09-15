/*
  ==============================================================================

    CircuitDisplay.cpp
    Created: 11 Sep 2022 8:26:55pm
    Author:  pwmag

  ==============================================================================
*/

#include "CircuitDisplay.h"

CircuitDisplay::CircuitDisplay(xynth::GuiData& g) : guiData(g) {
    gainSlider.init(g.audioProcessor.treeState, GAIN_ID);
    gainSlider.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainSlider.slider);

    gainSlider.slider.onValueChange = [this]() {
        getParentComponent()->repaint();
    };
}

void CircuitDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);

    gainSlider.slider.setBounds(rect.reduced(30));

    g.setColour(guiData.getLnf().getAccent1());
    g.setFont(guiData.getLnf().getCustomFontBold().withHeight(45));
    g.drawText("circuit", rect, juce::Justification::centred);
}