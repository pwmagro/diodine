/*
  ==============================================================================

    HueControl.h
    Created: 24 Sep 2022 6:16:13pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"
#include "../Utils/FullSlider.h"

namespace WDYM {
    class HueControl : public juce::Component {
    public:
        HueControl(xynth::GuiData& g);
        ~HueControl() { };
        void paint(juce::Graphics& g) override;

    private:
        xynth::FullSlider accentHue;

        xynth::GuiData& guiData;
    };
}