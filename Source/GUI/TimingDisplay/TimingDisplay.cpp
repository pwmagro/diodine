/*
  ==============================================================================

    TimingDisplay.cpp
    Created: 11 Sep 2022 8:25:57pm
    Author:  pwmag

  ==============================================================================
*/

#include "TimingDisplay.h"

TimingDisplay::TimingDisplay(xynth::GuiData& g) : guiData(g) {
    startTimerHz(60);

    trrSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    trrSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trrSlider.setTextBoxIsEditable(true);
    auto& treeState = g.audioProcessor.treeState;
    
    trrSlider.setName(TRR_NAME);
    trrSlider.setTextValueSuffix("ms");
    trrSlider.onValueChange = [this]() { repaint(); };

    trrAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, TRR_ID, trrSlider);

    addAndMakeVisible(trrSlider);
}

void TimingDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);
    rect.reduce(10, 10);

    auto labelRect = rect.removeFromBottom(20).withTrimmedLeft(10);
    g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(18));
    g.setColour(guiData.getLnf().getFgColor());
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

    g.setColour(guiData.getLnf().getTextColor());
    g.drawText(trrSlider.getTextFromValue(trrSlider.getValue()), textRect, juce::Justification::centred);
    
    rect.reduce(10, 10);
    rect.removeFromBottom(20.f);
    guiData.getLnf().drawGraphBackground(g, rect.toFloat(), 10);

    juce::Path scannerLine;
    scannerLine.startNewSubPath(rect.getX(), rect.getCentreY() - rect.getHeight() * 0.5 * (tanh(1)));

    float i = 0;
    for (; i < trrSlider.getValue(); i += 0.25) {
        scannerLine.lineTo(juce::Point<float>(rect.getX() + i * rect.getWidth() / trrSlider.getMaximum(), rect.getCentreY() - rect.getHeight() * 0.5 * (tanh(1) - tanh(i / trrSlider.getValue()))));
    }
    scannerLine.lineTo(juce::Point<float>(rect.getX() + i * rect.getWidth() / trrSlider.getMaximum(), rect.getCentreY()));

    scannerLine.lineTo(rect.getRight(), rect.getCentreY());
    g.setColour(guiData.getLnf().getFgColor().darker(0.4f));
    g.strokePath(scannerLine, juce::PathStrokeType(1.f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));
    g.setColour(guiData.getLnf().getTextColor().withSaturation(1.f));
    g.strokePath(scannerLine, juce::PathStrokeType(5.f * guiData.audioProcessor.getRrStatus(), juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));
}