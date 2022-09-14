/*
  ==============================================================================

    CustomLook.h
    Created: 5 Sep 2022 5:10:46pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Common/Constants.h"
#include "Styles.h"

namespace juce
{
    class CustomLook : public LookAndFeel_V4
    {
    public:
        CustomLook();

        // For debugging
        virtual String getLnfName() { return "CustomLook"; }

        // Custom draws
        virtual void drawSectionBackground(Graphics& g, Rectangle<int> area);
        virtual void drawGraphBackground(Graphics& g, Rectangle<float> area, float amplitude);
        virtual void drawGraphForeground(Graphics& g, Rectangle<float> area);
        virtual Image& getBackgroundImage() { return bgImage; };

        //==============================================================================
        // Sliders and buttons
        void drawCornerResizer(Graphics& g, int w, int h, bool, bool) override;

        void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional,
            float rotaryStartAngle, float rotaryEndAngle, Slider&) override;

        void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
            float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

        void drawToggleButton(Graphics&, ToggleButton&,
            bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

        //==============================================================================
        // Fonts and colours
        virtual Colour getAccent1() { return WDYM::TextColor; };
        virtual Colour getAccent2() { return WDYM::FgColor; };
        virtual Colour getNeutral1() { return WDYM::OutlineColor; };
        virtual Colour getBase1() { return WDYM::BgColor; };

        virtual const juce::Font getCustomFontRegular();
        virtual const juce::Font getCustomFontMedium();
        virtual const juce::Font getCustomFontSemiBold();
        virtual const juce::Font getCustomFontBold();

    private:
        Image bgImage;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLook)
    };
} // namespace juce