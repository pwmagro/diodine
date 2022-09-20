/*
  ==============================================================================

    CircuitDisplay.cpp
    Created: 11 Sep 2022 8:26:55pm
    Author:  pwmag

  ==============================================================================
*/

#include "CircuitDisplay.h"

CircuitDisplay::CircuitDisplay(xynth::GuiData& g) : guiData(g),
    diode1Switch(DIODE_1_NAME, juce::DrawableButton::ButtonStyle::ImageFitted),
    diode2Switch(DIODE_2_NAME, juce::DrawableButton::ButtonStyle::ImageFitted)
{
    gainSlider.init(g.audioProcessor.treeState, GAIN_ID);
    gainSlider.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainSlider.slider);

    mixSlider.init(g.audioProcessor.treeState, MIX_ID);
    mixSlider.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(mixSlider.slider);

    svg.diode_1_open_xml = juce::parseXML(BinaryData::diode_1_open_svg);
    svg.diode_1_open = juce::Drawable::createFromSVG(*svg.diode_1_open_xml);

    svg.diode_1_open->replaceColour(juce::Colours::black, WDYM::FgColor);

    svg.diode_2_open_xml = juce::parseXML(BinaryData::diode_2_open_svg);
    svg.diode_2_open = juce::Drawable::createFromSVG(*svg.diode_2_open_xml);
    svg.diode_2_open->replaceColour(juce::Colours::black, WDYM::FgColor);

    svg.diode_1_closed_xml = juce::parseXML(BinaryData::diode_1_closed_svg);
    svg.diode_1_closed = juce::Drawable::createFromSVG(*svg.diode_1_closed_xml);
    svg.diode_1_closed->replaceColour(juce::Colours::black, WDYM::FgColor);

    svg.diode_2_closed_xml = juce::parseXML(BinaryData::diode_2_closed_svg);
    svg.diode_2_closed = juce::Drawable::createFromSVG(*svg.diode_2_closed_xml);
    svg.diode_2_closed->replaceColour(juce::Colours::black, WDYM::FgColor);
    
    svg.opAmp_xml = juce::parseXML(BinaryData::op_amp_svg);
    svg.opAmp = juce::Drawable::createFromSVG(*svg.opAmp_xml);
    svg.opAmp->replaceColour(juce::Colours::black, WDYM::FgColor);

    diode1Switch.setImages(&(*svg.diode_1_open), nullptr, nullptr, nullptr, &(*svg.diode_1_closed));
    diode1Switch.setColour(diode1Switch.backgroundOnColourId, juce::Colours::transparentBlack);

    diode1Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(g.audioProcessor.treeState, DIODE_1_ID, diode1Switch);
    diode1Switch.setClickingTogglesState(true);
    addAndMakeVisible(diode1Switch);

    diode2Switch.setImages(&(*svg.diode_2_open), nullptr, nullptr, nullptr, &(*svg.diode_2_closed));
    diode2Switch.setColour(diode2Switch.backgroundOnColourId, juce::Colours::transparentBlack);
    diode2Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(g.audioProcessor.treeState, DIODE_2_ID, diode2Switch);
    diode2Switch.setClickingTogglesState(true);
    addAndMakeVisible(diode2Switch);

    auto repaintLambda = [this]() { getParentComponent()->repaint(); };
    gainSlider.slider.onValueChange = repaintLambda;
    mixSlider.slider.onValueChange = repaintLambda;
    diode1Switch.onStateChange = repaintLambda;
    diode2Switch.onStateChange = repaintLambda;
}

void CircuitDisplay::paint(juce::Graphics& g) {
    auto rect = getLocalBounds().toFloat();
    guiData.getLnf().drawSectionBackground(g, rect.toNearestInt());
    rect.reduce(20, 20);

    // Draw op amp
    auto leftRect = rect.removeFromLeft(rect.proportionOfWidth(0.075));
    auto topLeftRect = leftRect.removeFromTop(leftRect.getHeight() / 2.f);
    juce::Line<float> opAmpInPos (
        juce::Point<float>(leftRect.getX(), topLeftRect.getCentreY() - 15.f),
        juce::Point<float>(leftRect.getRight(), topLeftRect.getCentreY() - 15.f));
    juce::Line<float> opAmpInNeg1 (
        juce::Point<float>(leftRect.getRight() - 25.f, topLeftRect.getCentreY() + 15.f),
        juce::Point<float>(leftRect.getRight(), topLeftRect.getCentreY() + 15.f));
    juce::Line<float> opAmpInNeg2(
        juce::Point<float>(leftRect.getRight() - 25.f, topLeftRect.getCentreY() + 13.f), // 13 = 15 - 2, to compensate for line width
        juce::Point<float>(leftRect.getRight() - 25.f, topLeftRect.getBottom()));
    juce::Line<float> opAmpInNeg3(
        juce::Point<float>(leftRect.getRight() - 25.f, leftRect.getY()),
        juce::Point<float>(leftRect.getRight() - 25.f, leftRect.getCentreY()));
    juce::Line<float> opAmpInNeg4(
        juce::Point<float>(leftRect.getRight() - 27.f, leftRect.getCentreY()),
        juce::Point<float>(leftRect.getRight() + 75.f, leftRect.getCentreY()));
    g.setColour(WDYM::FgColor);
    g.drawLine(opAmpInPos, 4.f);
    g.drawLine(opAmpInNeg1, 4.f);
    g.drawLine(opAmpInNeg2, 4.f);
    g.drawLine(opAmpInNeg3, 4.f);
    g.drawLine(opAmpInNeg4, 4.f);

    leftRect = rect.removeFromLeft(55);
    topLeftRect = leftRect.removeFromTop(leftRect.getHeight() / 2.f);
    svg.opAmp->drawWithin(g, topLeftRect, juce::RectanglePlacement::centred, 1.f);
    gainSlider.slider.setBounds(leftRect.toNearestInt());

    // Connect op amp to diodes
    auto connectorRect = rect.removeFromLeft(rect.proportionOfWidth(0.1f));
    juce::Line<float> connector1(
        juce::Point<float>(connectorRect.getX() - 4.f, connectorRect.getY() + connectorRect.proportionOfHeight(0.25)),
        juce::Point<float>(connectorRect.getRight(), connectorRect.getY() + connectorRect.proportionOfHeight(0.25))
    );
    juce::Line<float> connector2(
        juce::Point<float>(connectorRect.getX() + 20.f, connectorRect.getY() + connectorRect.proportionOfHeight(0.25)),
        juce::Point<float>(connectorRect.getX() + 20.f, connectorRect.getY() + connectorRect.proportionOfHeight(0.75) + 2.f)
    );
    juce::Line<float> connector3(
        juce::Point<float>(connectorRect.getX() + 20.f, connectorRect.getY() + connectorRect.proportionOfHeight(0.75)),
        juce::Point<float>(connectorRect.getRight(), connectorRect.getY() + connectorRect.proportionOfHeight(0.75))
    );

    g.drawLine(connector1, 4.f);
    g.drawLine(connector2, 4.f);
    g.drawLine(connector3, 4.f);

    // Draw diodes
    auto diodeRect = rect.removeFromLeft(250);
    auto topDiodeRect = diodeRect.removeFromTop(diodeRect.proportionOfHeight(0.5f));
    diode1Switch.setBounds(topDiodeRect.toNearestInt());
    diode2Switch.setBounds(diodeRect.toNearestInt());

#ifdef JUCE_DEBUG
    // Ensure that rect has been scaled appropriately
    g.setColour(WDYM::TextColor.darker(2));
    g.fillRect(rect);
#endif
}