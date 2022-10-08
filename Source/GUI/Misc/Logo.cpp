/*
  ==============================================================================

    Logo.cpp
    Created: 11 Sep 2022 8:25:12pm
    Author:  pwmag

  ==============================================================================
*/

#include "Logo.h"

Logo::Logo(xynth::GuiData& g) : guiData(g), button(ABOUT_ID, juce::DrawableButton::ButtonStyle::ImageFitted) {
    logo_xml = juce::parseXML(BinaryData::diodine_logo_svg);
    logo_en_svg = juce::Drawable::createFromSVG(*logo_xml);
    logo_en_svg->setColour(100, juce::Colour::fromRGB(0x8a, 0xdf, 0xce));
    logo_en_svg->replaceColour(juce::Colours::black, guiData.getLnf().getFgColor());

    logo_svg = juce::Drawable::createFromSVG(*logo_xml);
    logo_svg->setColour(100, juce::Colour::fromRGB(0x8a, 0xdf, 0xce));
    logo_svg->replaceColour(logo_en_svg->findColour(100), guiData.getLnf().getTextColor().brighter(0.6).withRotatedHue(0.5));


    button.setImages(logo_svg.get(), nullptr, nullptr, nullptr, logo_en_svg.get());
    button.setColour(button.backgroundOnColourId, juce::Colours::transparentBlack);
    button.setClickingTogglesState(true);
    addAndMakeVisible(button);

    button.onStateChange = [this]() {
        juce::Component* a = this;
        while (a->getParentComponent() != nullptr) {
            a = a->getParentComponent();
        }
        a->repaint();
    };
}

void Logo::paint(juce::Graphics& g) {
    auto rect = getLocalBounds();
    guiData.getLnf().drawSectionBackground(g, rect);

    logo_en_svg->replaceColour(logo_en_svg->findColour(100), guiData.getLnf().getTextColor().brighter(0.6));
    logo_en_svg->setColour(100, guiData.getLnf().getTextColor().brighter(0.6));

    logo_svg->replaceColour(logo_svg->findColour(100), guiData.getLnf().getTextColor().brighter(0.6).withRotatedHue(0.5));
    logo_svg->setColour(100, guiData.getLnf().getTextColor().brighter(0.6).withRotatedHue(0.5));

    button.setImages(logo_svg.get(), nullptr, nullptr, nullptr, logo_en_svg.get());
    button.setBounds(rect.reduced(12, 12));
}

bool Logo::getButtonState() { return button.getToggleState(); };