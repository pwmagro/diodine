/*
  ==============================================================================

    Styles.h
    Created: 12 Sep 2022 5:00:54pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

namespace WDYM {
    class ColorGrabber : public juce::Component {
    public:
        ColorGrabber(xynth::GuiData& g) : guiData(g) {
            accentHue.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
            accentHue.onValueChange = [this]() { getParentComponent()->repaint(); };
            addAndMakeVisible(accentHue);
        }
        ~ColorGrabber() override;
        void paint(juce::Graphics& g) { accentHue.setBounds(getLocalBounds()); }
        juce::Colour FgColor() { juce::Colour::fromHSV(accentHue.getValue(), 0.1f, 0.5f, 1.f); }
        juce::Colour BgColor() { juce::Colour::fromHSV(accentHue.getValue(), 0.1f, 0.15f, 1.f); }
        juce::Colour TextColor() { juce::Colour::fromHSV(accentHue.getValue(), 0.8f, 0.9f, 1.f); }
        juce::Colour OutlineColor() { juce::Colour::fromHSV(accentHue.getValue(), 0.4f, 0.1f, 1.f); }


    private:
        xynth::GuiData& guiData;
        juce::Slider accentHue;
    };
}