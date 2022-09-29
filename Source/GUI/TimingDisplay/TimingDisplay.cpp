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

    trrMagSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    trrMagSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trrMagSlider.setTextBoxIsEditable(true);

    trrMagSlider.setName(TRR_MAG_NAME);
    trrMagSlider.setTextValueSuffix("");
    trrMagSlider.onValueChange = [this]() { repaint(); };

    trrMagAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, TRR_MAG_ID, trrMagSlider);

    addAndMakeVisible(trrSlider);
    addAndMakeVisible(trrMagSlider);
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

    auto labelRect = rect.removeFromBottom(20).withTrimmedLeft(10)
        
        ;
    g.drawText(((juce::String)TRR_NAME).toLowerCase(), labelRect, juce::Justification::left);

    auto sliderRect = rect.removeFromBottom(40);
    trrSlider.setBounds(sliderRect);

    g.setFont(lnf.getCustomFontRegular().withHeight(25));
    g.setColour(lnf.getTextColor());

    auto sliderPos = trrSlider.getPositionOfValue(trrSlider.getValue());
    auto newWidth = 80.f;
    float x = sliderRect.getX();
    float y = sliderRect.getY() - 25.f;
    auto width = trrSlider.getWidth();
    juce::Rectangle<float> textRect(std::min(std::max((sliderPos - 20.f), x + 10.f), x + width - 90.f), y, newWidth, 25.f);

    g.setColour(lnf.getTextColor());
    g.drawText(trrSlider.getTextFromValue(trrSlider.getValue()), textRect, juce::Justification::centred);
    
    rect.reduce(10, 10);
    rect.removeFromBottom(20.f);
    lnf.drawGraphBackground(g, rect.toFloat(), 4);

    juce::Path scannerLine;
    scannerLine.clear(); // i don't think this should be necessary but cant hurt, eh
    scannerLine.startNewSubPath(rect.getX(), rect.getCentreY());

    auto c = trrMagSlider.getValue() / trrMagSlider.getMaximum();

    float s = trrSlider.getValue() / trrSlider.getMaximum();
    for (float i = 0; i < s; i += 1 / (float)rect.getWidth()) {
        if (s < 0.001) break;
        double y = c * (12 * i / s) * pow(1 - (i / s), 4);
        scannerLine.lineTo(rect.getX() + i * rect.getWidth(), rect.getCentreY() - rect.getHeight() * 0.48 * y);
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
    g.setColour(lnf.getTextColor().withSaturation(0.8f).withRotatedHue(0.0625).darker(0.2f));
    g.strokePath(scannerLine, juce::PathStrokeType(3.f * guiData.audioProcessor.getRrStatus().right, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));

    // Draw a border
    g.setColour(lnf.getFgColor().darker(0.6));
    g.drawRoundedRectangle(rect.toFloat().expanded(2.f), 5.f, 4.f);
}