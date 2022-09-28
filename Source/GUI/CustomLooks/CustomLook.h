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
        virtual void drawBackgroundGradient(Graphics& g, Rectangle<int> area, float angle, juce::Colour from, juce::Colour to);

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
        virtual Colour getTextColor() { return WDYM::TextColor(hue); };
        virtual Colour getFgColor() { return WDYM::FgColor(hue); };
        virtual Colour getOutlineColor() { return WDYM::OutlineColor(hue); };
        virtual Colour getBgColor() { return WDYM::BgColor(hue); };

        virtual const juce::Font getCustomFontRegular();
        virtual const juce::Font getCustomFontMedium();
        virtual const juce::Font getCustomFontSemiBold();
        virtual const juce::Font getCustomFontBold();

        void setHue(float newHue) { hue = newHue; }


    private:
        Image bgImage;
        float hue = 0.47f;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLook)
    };
} // namespace juce