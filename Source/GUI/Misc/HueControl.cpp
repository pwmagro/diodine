/*
  ==============================================================================

    HueControl.cpp
    Created: 24 Sep 2022 6:16:13pm
    Author:  pwmag

  ==============================================================================
*/

#include "HueControl.h"

namespace WDYM {
    HueControl::HueControl(xynth::GuiData& g) : guiData(g) {
        accentHue.init(g.audioProcessor.treeState, HUE_ID);
        accentHue.slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        accentHue.slider.setRange(0, 360, 1);
        accentHue.slider.setRotaryParameters(0, 2 * juce::double_Pi, false);

        accentHue.slider.onValueChange = [this]() {
            guiData.getLnf().setHue(accentHue.slider.getValue() / 360.f);
            getParentComponent()->repaint();
        };

        addAndMakeVisible(accentHue.slider);
    }

    void HueControl::paint(juce::Graphics& g) {
        auto rect = getLocalBounds();
        guiData.getLnf().drawSectionBackground(g, rect);
        auto textRect = rect.removeFromBottom(25);
        accentHue.slider.setBounds(rect.reduced(2));

        auto& lnf = guiData.getLnf();

        g.setFont(lnf.getCustomFontRegular().withHeight(25));
        g.setColour(lnf.getFgColor());
        g.drawText(((juce::String)HUE_NAME).toLowerCase(), textRect, juce::Justification::centredTop);
    }
}