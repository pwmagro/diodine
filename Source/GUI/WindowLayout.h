/*
  ==============================================================================

    WindowLayout.h
    Created: 5 Sep 2022 3:26:44pm
    Author:  thesp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils/GuiData.h"
#include "About/AboutOverlay.h"
#include "CircuitDisplay/CircuitDisplay.h"
#include "OscilloscopeDisplay/OscilloscopeDisplay.h"
#include "VoltageDisplay/VoltageDisplay.h"
#include "TimingDisplay/TimingDisplay.h"
#include "Misc/Logo.h"
#include "Misc/HueControl.h"
#include "CustomLooks/Styles.h"

class WindowLayout : public juce::Component
{
public:
    WindowLayout(xynth::GuiData&);
    ~WindowLayout() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    float x = 0;
private:
    xynth::GuiData& guiData;

    // About overlay
    AboutOverlay aboutOverlay;

    // Contains circuit images, gain, mix, diode 1 & 2 enable, and remove DC offset
    CircuitDisplay circuitDisplay;

    // Contains oscilloscope and VU meter
    OscilloscopeDisplay oscilloscopeDisplay;

    // Contains waveshaper graph and Vf/Vb sliders
    VoltageDisplay voltageDisplay;

    // Contains timing display and trr slider
    TimingDisplay timingDisplay;

    // Miscellaneous items
    Logo logo;

    WDYM::HueControl hue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WindowLayout)
};
