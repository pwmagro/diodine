/*
  ==============================================================================

    VdSlider.h
    Created: 11 Sep 2022 8:31:16pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/GuiData.h"

#include "../Utils/FullSlider.h"

class VdSlider : public xynth::FullSlider {
public:
    VdSlider(xynth::GuiData& g);
};