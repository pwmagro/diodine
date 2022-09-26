/*
  ==============================================================================

    FixedWidthBuffer.h
    Created: 26 Sep 2022 3:48:05pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace WDYM {
    class FixedWidthBuffer {
    public:
        FixedWidthBuffer();
        FixedWidthBuffer(int width);
        ~FixedWidthBuffer();

        void process(juce::AudioBuffer<float>& buffer);
        float getSample(int i);
        int getWidth() { return width; }

    private:
        void writeSample(float sample);
        int width = 2050;
        std::vector<float> workingBuffer;
        std::vector<float> fullBuffer;
    };
}