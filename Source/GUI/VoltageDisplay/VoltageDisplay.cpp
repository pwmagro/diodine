/*
  ==============================================================================

    VoltageDisplay.cpp
    Created: 11 Sep 2022 8:39:10pm
    Author:  pwmag

  ==============================================================================
*/

#include "VoltageDisplay.h"


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
    guiData.getLnf().drawSectionBackground(g, rect);
    rect.reduce(10, 10);

    auto labelRects = rect.removeFromBottom(20);
    auto vfLabelRect = labelRects.withTrimmedLeft(rect.getWidth() / 2).withTrimmedLeft(10);
    auto vbLabelRect = labelRects.withTrimmedRight(rect.getWidth() / 2).withTrimmedLeft(10);

    g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(18));
    g.setColour(guiData.getLnf().getAccent2());
    g.drawText(((juce::String)VF_NAME).toLowerCase(), vfLabelRect, juce::Justification::left);
    g.drawText(((juce::String)VB_NAME).toLowerCase(), vbLabelRect, juce::Justification::left);
    // TODO draw sideways text for saturation bar name

    auto sliderRects = rect.removeFromBottom(40);
    auto vfSliderRect = sliderRects.withTrimmedLeft(rect.getWidth() / 2);
    auto vbSliderRect = sliderRects.withTrimmedRight(rect.getWidth() / 2);
    auto satSliderRect = rect.removeFromLeft(40).withTrimmedBottom(30);

    auto satTextRect = satSliderRect.translated(0, satSliderRect.getHeight() - 7.f);
    g.drawText(((juce::String)SAT_NAME).toLowerCase(), satTextRect, juce::Justification::centredTop);

    vfSlider.setBounds(vfSliderRect);
    vbSlider.setBounds(vbSliderRect);
    satSlider.setBounds(satSliderRect);

    g.setFont(guiData.getLnf().getCustomFontRegular().withHeight(25));
    g.setColour(guiData.getLnf().getAccent1());

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
}