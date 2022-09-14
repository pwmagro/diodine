/*
  ==============================================================================

    VfSlider.h
    Created: 11 Sep 2022 8:31:10pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/GuiData.h"

#include "../Utils/FullSlider.h"

class VfSlider : public xynth::FullSlider {
public:
    VfSlider(xynth::GuiData& g);
};