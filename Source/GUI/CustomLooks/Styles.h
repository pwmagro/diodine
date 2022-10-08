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
    static juce::Colour FgColor(float hue) { return juce::Colour::fromHSV(hue, 0.1f, 0.5f, 1.f); }
    static juce::Colour BgColor(float hue) { return juce::Colour::fromHSV(hue, 0.f, 0.15f, 1.f); }
    static juce::Colour TextColor(float hue) { return juce::Colour::fromHSV(hue, 0.8f, 0.9f, 1.f); }
    static juce::Colour OutlineColor(float hue) { return juce::Colour::fromHSV(hue, 0.f, 0.1f, 1.f); }
}
