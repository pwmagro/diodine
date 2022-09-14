/*
  ==============================================================================

    CustomLook.cpp
    Created: 5 Sep 2022 5:10:46pm
    Author:  thesp

  ==============================================================================
*/

#include "CustomLook.h"

namespace juce
{
    CustomLook::CustomLook()
    {
        // Ensures the background of popup menus is transparent
        // allows corners to be rounded
        setColour(PopupMenu::backgroundColourId, Colours::black.withAlpha(0.0f));
    }

    void CustomLook::drawSectionBackground(Graphics& g, Rectangle<int> area)
    {
        g.setColour(getBase1());
        g.fillRoundedRectangle(area.toFloat(), 5.f);
    }

    void CustomLook::drawGraphBackground(Graphics& g, Rectangle<float> area, float)
    {
        g.setColour(getBase1());
        g.fillRoundedRectangle(area, 8.f);

        g.setColour(getNeutral1().withAlpha(0.5f));
        g.drawLine(area.getCentreX(), area.getY(), area.getCentreX(), area.getBottom(), 2.f);
        g.drawLine(area.getX(), area.getCentreY(), area.getRight(), area.getCentreY(), 2.f);
    }

    void CustomLook::drawGraphForeground(Graphics& g, Rectangle<float> area)
    {
        g.setColour(getAccent2());
        g.drawRoundedRectangle(area.reduced(0.75f), 8.f, 2.f);
    }

    void CustomLook::drawCornerResizer(Graphics& g, int w, int h, bool, bool)
    {}

    void CustomLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
    {
        // If mouse is hovering over
        const bool highlight = slider.isMouseOverOrDragging();

        // Radius of knob
        float radius = juce::jmin(width / 2, height / 2);
        const bool isLarge = radius > 25.f;

        // Centre point (centreX, centreY) of knob
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;

        float thickness = (highlight ? 5.f : 4.4f) * (isLarge ? 1.f : 0.6f);

        // Draw background circle
        Rectangle<float> rect(x, y, width, height);
        rect = rect.withSizeKeepingCentre(radius * 2.f, radius * 2.f);
        g.setColour(getBase1());
        g.fillEllipse(rect.reduced(0.1f));

        // current angle of the slider
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        radius = juce::jmin(width / 2, height / 2) - thickness * 0.5f;

        const auto bgColour = getNeutral1();
        const auto mainColour = isLarge ? getAccent1() : getAccent2();

        // Draw path of the slider backgound (in darker background colour)
        juce::Path backgroundArc;
        backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
        g.setColour(bgColour);
        g.strokePath(backgroundArc, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        // Draw path of slider foreground (in white)
        juce::Path foregroundArc;
        foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
        g.setColour(mainColour);
        g.strokePath(foregroundArc, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

        if (isLarge)
        {
            g.setFont(getCustomFontMedium().withHeight(30));
            g.drawText(String(std::round(slider.getValue())), rect, Justification::centred);
        }
    }

    void CustomLook::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
    {

        auto rect = juce::Rectangle<float>(x, y, width, height).reduced(2.f);

        bool isHovered = slider.isMouseOverOrDragging();
        bool isHorizontal = slider.isHorizontal();

        // Slider track
        Point<float> start = isHorizontal ? Point<float>(x, y + (height / 2.f)) : Point<float>(x + (width / 2.f), y);
        Point<float> end = isHorizontal ? Point<float>(x + width, y + (height / 2.f)) : Point<float>(x + (width / 2.f), y + height);
        g.setColour(getAccent2());
        g.setOpacity(isHovered ? 1.f : 0.75f);
        g.drawLine(Line<float>(start, end), 4.f);

        g.setColour(getAccent1());

        float newWidth = 6.f;
        if (isHovered)
            newWidth = std::max((double)6.f, (isHorizontal ? width : height) * 0.15);
        else
            newWidth = 6.f;

        Rectangle<float> knob; 
        knob = (isHorizontal ?
            Rectangle<float>(jmin<float>(jmax<float>(sliderPos - (newWidth / 2.f), x), x + width - newWidth), (height * 0.2), newWidth, (height * 0.6))
          : Rectangle<float>((width * 0.2), jmin<float>(jmax<float>(sliderPos - (newWidth / 2.f), y), y + height - newWidth), (width * 0.6), newWidth)
        );
        g.fillRoundedRectangle(knob, 3.f);
    }
    
    void CustomLook::drawToggleButton(Graphics& g, ToggleButton& button,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        auto rect = button.getLocalBounds().toFloat();

        // Draw background
        auto bgColour = button.getToggleState() ? getAccent2() : getNeutral1();
        bgColour = bgColour.brighter(shouldDrawButtonAsHighlighted ? 0.1f : 0.f);
        bgColour = bgColour.darker(shouldDrawButtonAsDown ? 0.2f : 0.f);
        g.setColour(bgColour);
        g.fillRoundedRectangle(rect, 6.f);

        // Draw power symbol
        g.setColour(getBase1());
        const float centreX = rect.getCentreX();
        const float centreY = rect.getCentreY();

        Path p;
        const float margin = 0.5f;
        p.addCentredArc(centreX, centreY, 5.f, 5.f, 1.5708f, -margin, 3.14 + margin, true);

        p.startNewSubPath(centreX, centreY - 2.f);
        p.lineTo(centreX, centreY - 5.f);

        g.strokePath(p, juce::PathStrokeType(2.5f, juce::PathStrokeType::mitered, juce::PathStrokeType::rounded));
    }

    const juce::Font CustomLook::getCustomFontRegular()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(FONT_LIGHT, FONT_LIGHT_SIZE);
        return juce::Font(typeface).withHeight(21.f);
    }
    const juce::Font CustomLook::getCustomFontMedium()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(FONT_MAIN, FONT_MAIN_SIZE);
        return juce::Font(typeface).withHeight(36.f);
    }
    const juce::Font CustomLook::getCustomFontSemiBold()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(FONT_BOLD, FONT_BOLD_SIZE);
        return juce::Font(typeface).withHeight(44.f);
    }
    const juce::Font CustomLook::getCustomFontBold()
    {
        static auto typeface = juce::Typeface::createSystemTypefaceFor(FONT_BOLD, FONT_BOLD_SIZE);
        return juce::Font(typeface).withHeight(28.f);
    }
} // namespace juce