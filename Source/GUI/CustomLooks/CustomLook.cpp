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

    void CustomLook::drawBackgroundGradient(Graphics& g, Rectangle<int> area, float angle, juce::Colour from, juce::Colour to) {
        if (angle >= 0 && angle < 90) {
            // do this later.
        }

        juce::ColourGradient grad(to, area.getRight() + area.getWidth() * 0.25f, area.getY(), from, area.getRight() + area.getWidth() * 0.25f, area.getBottom(), true);
        g.setGradientFill(grad);
        g.fillRect(area);
    }

    void CustomLook::drawSectionBackground(Graphics& g, Rectangle<int> area)
    {
        
    }

    void CustomLook::drawGraphBackground(Graphics& g, Rectangle<float> area, float amplitude = 1)
    {
        const float division = 7;
        const int   divisint = (int)division;
        float lineFreq = std::pow(2, std::max(((int)(amplitude) / divisint), 1));
        float lineFreqSmall = std::pow(2, std::max(((int)(amplitude + division) / divisint), 1));
        float smallOpacity = ((amplitude / division) - (int)(amplitude / division));

        g.setColour(getOutlineColor());
        g.fillRoundedRectangle(area, 3.f);

        g.setColour(getFgColor().withAlpha(0.1f));
        g.drawLine(area.getCentreX(), area.getY(), area.getCentreX(), area.getBottom(), 1.f);
        g.drawLine(area.getX(), area.getCentreY(), area.getRight(), area.getCentreY(), 1.f);

        g.setColour(getFgColor().withAlpha(0.4f * (1 - smallOpacity)));
        for (float i = 0; i < amplitude; i += lineFreq) {
            auto x = area.getWidth() * i / (amplitude * 2);
            g.drawLine(area.getCentreX() + x, area.getY(), area.getCentreX() + x, area.getBottom(), 1.f);
            g.drawLine(area.getCentreX() - x, area.getY(), area.getCentreX() - x, area.getBottom(), 1.f);
        }

        for (float j = 0; j <= amplitude; j += lineFreq) {
            auto y = area.getHeight() * j / (amplitude * 2);
            g.drawLine(area.getX(), area.getCentreY() + y, area.getRight(), area.getCentreY() + y, 1.f);
            g.drawLine(area.getX(), area.getCentreY() - y, area.getRight(), area.getCentreY() - y, 1.f);
        }

        g.setOpacity(0.4f * smallOpacity);
        for (float i = 0; i < amplitude; i += lineFreqSmall) {
            auto x = area.getWidth() * i / (amplitude * 2);
            g.drawLine(area.getCentreX() + x, area.getY(), area.getCentreX() + x, area.getBottom(), 1.f);
            g.drawLine(area.getCentreX() - x, area.getY(), area.getCentreX() - x, area.getBottom(), 1.f);
        }

        for (float j = 0; j <= amplitude; j += lineFreqSmall) {
            auto y = area.getHeight() * j / (amplitude * 2);
            g.drawLine(area.getX(), area.getCentreY() + y, area.getRight(), area.getCentreY() + y, 1.f);
            g.drawLine(area.getX(), area.getCentreY() - y, area.getRight(), area.getCentreY() - y, 1.f);
        }
    }

    void CustomLook::drawGraphForeground(Graphics& g, Rectangle<float> area)
    {
        g.setColour(getFgColor());
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
        g.setColour(getBgColor());
        g.fillEllipse(rect.reduced(0.1f));

        // current angle of the slider
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        radius = juce::jmin(width / 2, height / 2) - thickness * 0.5f;

        const auto bgColour = getOutlineColor();
        const auto mainColour = isLarge ? getTextColor() : getFgColor();

        // Draw path of the slider backgound (in darker background colour)
        juce::Path backgroundArc;
        backgroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
        g.setColour(bgColour);
        g.strokePath(backgroundArc, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));


        if (slider.getRotaryParameters().stopAtEnd) {    
            // Draw path of slider foreground (in white)
            juce::Path foregroundArc;
            foregroundArc.addCentredArc(centreX, centreY, radius, radius, 0.0f, rotaryStartAngle, angle, true);
            g.setColour(mainColour);
            g.strokePath(foregroundArc, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }

        else {
            juce::Point<float> start(centreX + 0.6f * radius * cos(angle), centreY + 0.6f * radius * sin(angle));
            juce::Point<float> end(centreX + radius * cos(angle), centreY + radius * sin(angle));
            juce::Path indicator;
            indicator.startNewSubPath(start);
            indicator.lineTo(end);
            g.setColour(mainColour);
            g.strokePath(indicator, juce::PathStrokeType(thickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }

        if (isLarge && slider.getRotaryParameters().stopAtEnd)
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
        g.setColour(getFgColor().darker(0.5f));
        g.setOpacity(isHovered ? 1.f : 0.75f);
        g.drawLine(Line<float>(start, end), 4.f);

        g.setColour(getTextColor());

        float newWidth = 6.f;
        if (isHovered)
            newWidth = 8.f;
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
        auto bgColour = button.getToggleState() ? getFgColor() : getOutlineColor();
        bgColour = bgColour.brighter(shouldDrawButtonAsHighlighted ? 0.1f : 0.f);
        bgColour = bgColour.darker(shouldDrawButtonAsDown ? 0.2f : 0.f);
        g.setColour(bgColour);
        g.fillRoundedRectangle(rect, 6.f);

        // Draw power symbol
        g.setColour(getBgColor());
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