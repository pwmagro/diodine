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
    startTimerHz(60);
    auto& treeState = g.audioProcessor.treeState;

    // Slider visuals
    auto visualSetup = [](juce::Slider& slider, bool vertical, juce::String name) {
        slider.setSliderStyle(vertical ? juce::Slider::SliderStyle::LinearVertical : juce::Slider::SliderStyle::LinearHorizontal);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        slider.setTextBoxIsEditable(true);
        slider.setName(name);
        slider.setTextValueSuffix("V");
        slider.setNumDecimalPlacesToDisplay(1);
    };
    visualSetup(vfSlider, false, VF_NAME);
    visualSetup(vbSlider, false, VB_NAME);
    visualSetup(satSlider, true, SAT_NAME);

    // Slider attachments
    vfAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, VF_ID, vfSlider);
    vbAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, VB_ID, vbSlider);
    satAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, SAT_ID, satSlider);

    // Value change lambdas
    auto onValueChange = [this]() { repaint(); };
    vfSlider.onValueChange = onValueChange;
    vbSlider.onValueChange = onValueChange;
    satSlider.onValueChange = onValueChange;

    // Register(?) sliders
    addAndMakeVisible(vfSlider);
    addAndMakeVisible(vbSlider);
    addAndMakeVisible(satSlider);

};

void VoltageDisplay::paint(juce::Graphics& g) {
    
    // rect = whole section box
    auto rect = getLocalBounds();
    auto& lnf = guiData.getLnf();

    // draw background and add margins
    lnf.drawSectionBackground(g, rect);
    rect.reduce(10, 10);

    // Saturation slider owns left 40px of the section
    auto satSliderRect = rect.removeFromLeft(40).withTrimmedBottom(80);
    auto satTextRect = satSliderRect.translated(0, satSliderRect.getHeight() - 7.f);
    g.setFont(lnf.getCustomFontRegular().withHeight(22));
    g.setColour(lnf.getFgColor());
    g.drawText(((juce::String)SAT_NAME).toLowerCase(), satTextRect, juce::Justification::centredTop);
    satSlider.setBounds(satSliderRect);

    // Voltage slider labels own bottom 20px of the section
    auto labelRects = rect.removeFromBottom(20);
    auto vfLabelRect = labelRects.withTrimmedLeft(rect.getWidth() / 2).withTrimmedLeft(10);
    auto vbLabelRect = labelRects.withTrimmedRight(rect.getWidth() / 2).withTrimmedLeft(10);

    // Draw slider labels
    g.drawText(((juce::String)VF_NAME).toLowerCase(), vfLabelRect, juce::Justification::left);
    g.drawText(((juce::String)VB_NAME).toLowerCase(), vbLabelRect, juce::Justification::left);

    // Voltage sliders own next bottom 40px of the section
    auto sliderRects = rect.removeFromBottom(40);
    auto vfSliderRect = sliderRects.withTrimmedLeft(rect.getWidth() / 2);
    auto vbSliderRect = sliderRects.withTrimmedRight(rect.getWidth() / 2);
    vfSlider.setBounds(vfSliderRect);
    vbSlider.setBounds(vbSliderRect);

    // Slider values
    g.setFont(lnf.getCustomFontRegular().withHeight(25));
    g.setColour(lnf.getTextColor());

    // Find the location of the slider knob
    auto vfSliderPos = vfSlider.getPositionOfValue(vfSlider.getValue());
    auto vbSliderPos = vbSlider.getPositionOfValue(vbSlider.getValue());

    // Set a "wall" so labels don't go left or right of the slider
    auto newWidth = 80.f;
    float vfx = vfSliderRect.getX();
    float vfy = vfSliderRect.getY() - 25.f;
    auto width = vfSlider.getWidth();
    juce::Rectangle<float> vfTextRect(std::min(std::max((vfSliderPos + vfx - (newWidth / 2.f)), vfx), vfSliderRect.getRight() - newWidth), vfy, newWidth, 25.f);
    g.drawText(vfSlider.getTextFromValue(vfSlider.getValue()), vfTextRect, juce::Justification::centred);

    float vbx = vbSliderRect.getX();
    float vby = vbSliderRect.getY() - 25.f;
    width = vbSlider.getWidth();
    juce::Rectangle<float> vbTextRect(std::min(std::max((vbSliderPos + vbx - (newWidth / 2.f)), vbx), vbSliderRect.getRight() - newWidth), vby, newWidth, 25.f);
    g.drawText(vbSlider.getTextFromValue(vbSlider.getValue()), vbTextRect, juce::Justification::centred);

    // Create the waveshaper graph
    drawWaveshaper(rect, g);

    // Draw a border
    g.setColour(guiData.getLnf().getFgColor().darker(0.6));
    
}

void VoltageDisplay::drawWaveshaper(juce::Rectangle<int> rect, juce::Graphics& g) {
    // Setup
    auto& lnf = guiData.getLnf();
    rect.reduce(10, 10);
    rect.removeFromBottom(20.f);
    auto gain = guiData.audioProcessor.treeState.getRawParameterValue(GAIN_ID)->load();
    
    // Create the background
    lnf.drawGraphBackground(g, rect.toFloat(), gain);
    
    // Get waveshaper output for each input from -1 to 1 and connect the dots
    waveshape.clear();
    auto& apvts = guiData.audioProcessor.treeState;
    auto firstPoint = juce::Point<float>(
        rect.getX(),
        rect.getCentreY() - (WDYM::Diode::waveshape(-1, apvts) * rect.getHeight() / 2.f));
    waveshape.startNewSubPath(firstPoint);
    for (float i = -0.99; i <= 1.01f; i += 0.02) {
        auto point = juce::Point<float>(
            rect.getCentreX() + (i * rect.getWidth() / 2),
            rect.getCentreY() - (WDYM::Diode::waveshape(i, apvts) * rect.getHeight() / 2.f) );

        waveshape.lineTo(point);
    }

    // Draw the line
    g.setColour(guiData.getLnf().getFgColor().darker(0.35f));
    g.strokePath(waveshape, juce::PathStrokeType(2.f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));

    // Draw audio shape
    // TODO: modify ringbuffer class to supply separate pos and neg values
    waveshape.clear();
    auto xmaxmin = guiData.audioProcessor.readRingBuffer();
    auto xPos = xmaxmin.max;
    auto xNeg = xmaxmin.min;
    if (xPos < lastXPos)
        xPos = lastXPos * 0.92;
    if (xNeg > lastXNeg)
        xNeg = lastXNeg * 0.92;
    
    lastXPos = xPos;
    lastXNeg = xNeg;

    firstPoint = juce::Point<float>(
        rect.getCentreX() + (xNeg * rect.getWidth() / 2),
        rect.getCentreY() - (WDYM::Diode::waveshape(xNeg, apvts) * rect.getHeight() / 2.f));
    waveshape.startNewSubPath(firstPoint);

    for (float i = xNeg; i < xPos; i += 0.02) {
        auto point = juce::Point<float>(
            rect.getCentreX() + (i * rect.getWidth() / 2),
            rect.getCentreY() - (WDYM::Diode::waveshape(i, apvts) * rect.getHeight() / 2.f));

        waveshape.lineTo(point);
    }

    g.saveState();
    g.reduceClipRegion(rect.toNearestInt());

    g.setColour(guiData.getLnf().getTextColor().withSaturation(1.f));
    g.strokePath(waveshape, juce::PathStrokeType(std::min(3.f, 24.f * xPos), juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded));

    g.restoreState();
    g.drawRoundedRectangle(rect.toFloat().expanded(2.f), 5.f, 4.f);
}

void VoltageDisplay::timerCallback() {
    repaint();
}