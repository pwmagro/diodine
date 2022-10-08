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

    trrMagSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    trrMagSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trrMagSlider.setTextBoxIsEditable(true);

    trrMagSlider.setName(TRR_MAG_NAME);
    trrMagSlider.setTextValueSuffix("");
    trrMagSlider.onValueChange = [this]() { repaint(); };

    trrSkew.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    trrSkew.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trrSkew.setTextBoxIsEditable(true);

    trrSkew.setName(TRR_SKEW_NAME);
    trrSkew.setTextValueSuffix("");
    trrSkew.onValueChange = [this]() { repaint(); };

    trrAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, TRR_ID, trrSlider);
    trrMagAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, TRR_MAG_ID, trrMagSlider);
    skewAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, TRR_SKEW_ID, trrSkew);

    addAndMakeVisible(trrSlider);
    addAndMakeVisible(trrMagSlider);
    addAndMakeVisible(trrSkew);
}

void TimingDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    auto& lnf = guiData.getLnf();

    lnf.drawSectionBackground(g, rect);
    rect.reduce(10, 10);

    auto vertSliderRect = rect.removeFromLeft(40).withTrimmedBottom(80);
    auto gainTextRect = vertSliderRect.translated(0, vertSliderRect.getHeight() - 7.f);
    g.setFont(lnf.getCustomFontRegular().withHeight(22));
    g.setColour(lnf.getFgColor());
    g.drawText(((juce::String)"mag").toLowerCase(), gainTextRect, juce::Justification::centredTop);
    trrMagSlider.setBounds(vertSliderRect);

    auto labelRect = rect.removeFromBottom(20).withTrimmedLeft(10);
    g.drawText(((juce::String)"Time").toLowerCase(), labelRect.withTrimmedLeft(labelRect.getWidth() / 2.f), juce::Justification::left);
    g.drawText(((juce::String)"Skew").toLowerCase(), labelRect.withTrimmedRight(labelRect.getWidth() / 2.f), juce::Justification::left);

    auto sliderRect = rect.removeFromBottom(40);
    auto trrRect = sliderRect.removeFromRight(sliderRect.getWidth() / 2.f);
    trrSlider.setBounds(trrRect);
    trrSkew.setBounds(sliderRect);

    g.setFont(lnf.getCustomFontRegular().withHeight(25));
    g.setColour(lnf.getTextColor());

    auto sliderPos = trrSlider.getPositionOfValue(trrSlider.getValue());
    auto newWidth = 80.f;
    float x = trrRect.getX();
    float y = trrRect.getY() - 25.f;
    auto width = trrSlider.getWidth();
    juce::Rectangle<float> textRect(std::min(std::max((sliderPos + x - (newWidth / 2.f)), x), trrRect.getRight() - newWidth), y, newWidth, 25.f);

    g.setColour(lnf.getTextColor());
    g.drawText(trrSlider.getTextFromValue(trrSlider.getValue()), textRect, juce::Justification::centred);
    
    rect.reduce(10, 10);
    rect.removeFromBottom(20.f);
    lnf.drawGraphBackground(g, rect.toFloat(), 4);

    juce::Path scannerLine;
    scannerLine.clear(); // i don't think this should be necessary but cant hurt, eh
    scannerLine.startNewSubPath(rect.getX(), rect.getCentreY());

    auto tension = trrSkew.getValue();
    auto mag = trrMagSlider.getValue();

    float s = trrSlider.getValue() / trrSlider.getMaximum();
    for (float i = 0; i < tension; i += 1 / (float)rect.getWidth()) {
        // First section
        auto y = -(i / pow(tension, 2)) * (2 * tension - i) * mag;
        scannerLine.lineTo(rect.getX() + rect.getWidth() * i * s, rect.getCentreY() + y * rect.getHeight() * 0.47);
        if (s < 0.001) break;
    }

    for (float i = tension; i < 1; i += 1 / (float)rect.getWidth()) {
        // Second section
        auto y = pow((i - 1) * (i + (1 - 2 * tension)) / ((tension - 1) * (1 - tension)), 2) * mag;
        scannerLine.lineTo(rect.getX() + rect.getWidth() * i * s, rect.getCentreY() - y * rect.getHeight() * 0.47);
        if (s < 0.001) break;
    }

    scannerLine.lineTo(juce::Point<float>(rect.getX() + rect.getWidth() * (trrSlider.getValue() / trrSlider.getMaximum()), rect.getCentreY()));

    scannerLine.lineTo(rect.getRight(), rect.getCentreY());
    g.setColour(lnf.getFgColor().darker(0.4f));
    g.strokePath(scannerLine, juce::PathStrokeType(1.f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));
    g.setColour(lnf.getTextColor().withSaturation(0.8f).withRotatedHue(-0.0625).darker(0.2f));
    g.strokePath(scannerLine, juce::PathStrokeType(3.f * guiData.audioProcessor.getRrStatus().left, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));
    
    scannerLine.applyTransform(juce::AffineTransform::translation(0, rect.getHeight() / 2));

    g.setColour(lnf.getFgColor().darker(0.4f));
    g.strokePath(scannerLine, juce::PathStrokeType(1.f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));
    g.setColour(lnf.getTextColor().withSaturation(0.8f).withRotatedHue(0.0725).darker(0.2f));
    g.strokePath(scannerLine, juce::PathStrokeType(3.f * guiData.audioProcessor.getRrStatus().right, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));

    // Draw a border
    g.setColour(lnf.getFgColor().darker(0.6));
    g.drawRoundedRectangle(rect.toFloat().expanded(2.f), 5.f, 4.f);
}