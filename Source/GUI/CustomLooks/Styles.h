/*
  ==============================================================================

    Styles.h
    Created: 12 Sep 2022 5:00:54pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace WDYM {
    static const float accentHue = 0;
    static const juce::Colour FgColor = juce::Colour::fromHSV(accentHue, 0.1f, 0.5f, 1.f);
    static const juce::Colour BgColor = juce::Colour::fromHSV(accentHue, 0.1f, 0.15f, 1.f);
    static const juce::Colour TextColor = juce::Colour::fromHSV(accentHue, 0.8f, 0.9f, 1.f);
    static const juce::Colour OutlineColor = juce::Colour::fromHSV(accentHue, 0.4f, 0.1f, 1.f);
}