/*
  ==============================================================================

    TimingDisplay.cpp
    Created: 11 Sep 2022 8:25:57pm
    Author:  pwmag

  ==============================================================================
*/

#include "TimingDisplay.h"

TimingDisplay::TimingDisplay(xynth::GuiData& g) : guiData(g) {
    trrSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    trrSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trrSlider.setTextBoxIsEditable(true);
    auto& treeState = g.audioProcessor.treeState;
    
    trrSlider.setName(TRR_NAME);
    trrSlider.setTextValueSuffix("ms");

    trrAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, TRR_ID, trrSlider);

    trrSlider.onValueChange = [this]() {
        this->repaint();
    };

    addAndMakeVisible(trrSlider);
}

void TimingDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);
    rect.reduce(10, 10);

    auto labelRect = rect.removeFromBottom(20).withTrimmedLeft(10);
    g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(18));
    g.setColour(guiData.getLnf().getAccent2());
    g.drawText(((juce::String)TRR_NAME).toLowerCase(), labelRect, juce::Justification::left);

    auto sliderRect = rect.removeFromBottom(40);
    trrSlider.setBounds(sliderRect);

    sliderRect.reduce(2.f, 2.f);
    g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(25));

    auto sliderPos = trrSlider.getPositionOfValue(trrSlider.getValue());
    auto newWidth = 80.f;
    float x = sliderRect.getX();
    float y = sliderRect.getY() - 25.f;
    auto width = trrSlider.getWidth();
    juce::Rectangle<float> textRect(std::min(std::max((sliderPos - 20.f), x + 10.f), x + width - 90.f), y, newWidth, 25.f);

    g.setColour(guiData.getLnf().getAccent1());
    g.drawText(trrSlider.getTextFromValue(trrSlider.getValue()), textRect, juce::Justification::centred);
    
}