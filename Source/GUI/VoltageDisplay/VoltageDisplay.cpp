/*
  ==============================================================================

    VoltageDisplay.cpp
    Created: 11 Sep 2022 8:39:10pm
    Author:  pwmag

  ==============================================================================
*/

#include "VoltageDisplay.h"
#include <cmath>


VoltageDisplay::VoltageDisplay(xynth::GuiData& g) : guiData(g)
{
    vfSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    vfSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    vfSlider.setTextBoxIsEditable(true);
    auto& treeState = g.audioProcessor.treeState;

    vfSlider.setName(VF_NAME);
    vfSlider.setTextValueSuffix("V");
    vfSlider.setNumDecimalPlacesToDisplay(1);

    vfAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, VF_ID, vfSlider);

    vfSlider.onValueChange = [this]() {
        this->repaint();
    };

    addAndMakeVisible(vfSlider);


    vbSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    vbSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    vbSlider.setTextBoxIsEditable(true);

    vbSlider.setName(VB_NAME);
    vbSlider.setTextValueSuffix("V");
    vbSlider.setNumDecimalPlacesToDisplay(1);

    vbAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, VB_ID, vbSlider);

    vbSlider.onValueChange = [this]() {
        this->repaint();
    };

    addAndMakeVisible(vbSlider);


    satSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    satSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    satSlider.setTextBoxIsEditable(true);

    satSlider.setName(SAT_NAME);
    satSlider.setTextValueSuffix("V");
    satSlider.setNumDecimalPlacesToDisplay(1);

    satAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, SAT_ID, satSlider);

    satSlider.onValueChange = [this]() {
        this->repaint();
    };

    addAndMakeVisible(satSlider);

};

void VoltageDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    auto& lnf = guiData.getLnf();
    lnf.drawSectionBackground(g, rect);
    rect.reduce(10, 10);

    auto satSliderRect = rect.removeFromLeft(40).withTrimmedBottom(80);

    auto labelRects = rect.removeFromBottom(20);
    auto vfLabelRect = labelRects.withTrimmedLeft(rect.getWidth() / 2).withTrimmedLeft(10);
    auto vbLabelRect = labelRects.withTrimmedRight(rect.getWidth() / 2).withTrimmedLeft(10);

    g.setFont(lnf.getCustomFontRegular().withHeight(18));
    g.setColour(lnf.getAccent2());
    g.drawText(((juce::String)VF_NAME).toLowerCase(), vfLabelRect, juce::Justification::left);
    g.drawText(((juce::String)VB_NAME).toLowerCase(), vbLabelRect, juce::Justification::left);
    // TODO draw sideways text for saturation bar name

    auto sliderRects = rect.removeFromBottom(40);
    auto vfSliderRect = sliderRects.withTrimmedLeft(rect.getWidth() / 2);
    auto vbSliderRect = sliderRects.withTrimmedRight(rect.getWidth() / 2);

    auto satTextRect = satSliderRect.translated(0, satSliderRect.getHeight() - 7.f);
    g.drawText(((juce::String)SAT_NAME).toLowerCase(), satTextRect, juce::Justification::centredTop);

    vfSlider.setBounds(vfSliderRect);
    vbSlider.setBounds(vbSliderRect);
    satSlider.setBounds(satSliderRect);

    g.setFont(lnf.getCustomFontRegular().withHeight(25));
    g.setColour(lnf.getAccent1());

    auto vfSliderPos = vfSlider.getPositionOfValue(vfSlider.getValue());
    auto vbSliderPos = vbSlider.getPositionOfValue(vbSlider.getValue());

    auto newWidth = 80.f;
    
    float vfx = vfSliderRect.getX();
    float vfy = vfSliderRect.getY() - 25.f;
    auto width = vfSlider.getWidth();
    juce::Rectangle<float> vfTextRect(std::min(std::max((vfSliderPos - 20.f), vfx + 10.f), vfx + width - 90.f), vfy, newWidth, 25.f);

    g.drawText(vfSlider.getTextFromValue(vfSlider.getValue()), vfTextRect, juce::Justification::centred);

    float vbx = vbSliderRect.getX();
    float vby = vbSliderRect.getY() - 25.f;
    width = vbSlider.getWidth();
    juce::Rectangle<float> vbTextRect(std::min(std::max((vbSliderPos - 20.f), vbx + 10.f), vbx + width - 90.f), vby, newWidth, 25.f);

    g.drawText(vbSlider.getTextFromValue(vbSlider.getValue()), vbTextRect, juce::Justification::centred);

    drawWaveshaperLine(rect, g);
    
}

void VoltageDisplay::drawWaveshaperLine(juce::Rectangle<int> rect, juce::Graphics& g) {
    auto& lnf = guiData.getLnf();
    rect.reduce(10, 10);
    rect.removeFromBottom(20.f);
    auto gain = guiData.audioProcessor.treeState.getRawParameterValue(GAIN_ID)->load();
    lnf.drawGraphBackground(g, rect.toFloat(), gain);
    waveshape.clear();
    auto& apvts = guiData.audioProcessor.treeState;
    auto firstPoint = juce::Point<float>(
        rect.getX(),
        rect.getCentreY() - (WDYM::Diode::waveshape(-1, apvts) * rect.getHeight() / 2.f));
    waveshape.startNewSubPath(firstPoint);
    for (float i = -0.98; i <= 1.001f; i += 0.02) {
        auto point = juce::Point<float>(
            rect.getCentreX() + (i * rect.getWidth() / 2),
            rect.getCentreY() - (WDYM::Diode::waveshape(i, apvts) * rect.getHeight() / 2.f) );

        waveshape.lineTo(point);
    }
    g.setColour(WDYM::FgColor);
    g.strokePath(waveshape, juce::PathStrokeType(4.f, juce::PathStrokeType::curved));

    g.setColour(WDYM::TextColor.darker(2));
    g.drawRoundedRectangle(rect.toFloat().expanded(2.f), 10.f, 4.f);
}