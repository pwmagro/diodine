/*
  ==============================================================================

    FixedWidthBuffer.cpp
    Created: 26 Sep 2022 3:48:05pm
    Author:  pwmag

  ==============================================================================
*/

#include "FixedWidthBuffer.h"

namespace WDYM {
    FixedWidthBuffer::FixedWidthBuffer() {
        workingBuffer.resize(width);
        fullBuffer.resize(width);
    }

    FixedWidthBuffer::FixedWidthBuffer(int width) {
        this->width = width;
    }

    FixedWidthBuffer::~FixedWidthBuffer() {
    }

    void FixedWidthBuffer::process(juce::AudioBuffer<float>& buffer) {
        if (buffer.getNumChannels() != 2) {
            throw std::exception("Only 2 input channels are supported!");
        }

        auto leftBuff = buffer.getReadPointer(0);
        auto rightBuff = buffer.getReadPointer(1);

        for (int i = 0; i < buffer.getNumSamples(); i++) {
            writeSample((leftBuff[i] + rightBuff[i]) * 0.5);
        }
    }

    void FixedWidthBuffer::writeSample(float sample) {
        static float workingIndex = 0;

        if (workingIndex < width) {
            workingBuffer.push_back(sample);
            workingIndex++;
        }

        else {
            fullBuffer = workingBuffer;
            workingBuffer.clear();
            workingIndex = 0;
        }
    }

    float FixedWidthBuffer::getSample(int i) {
        if (i < 0 || i >= width) {
            throw std::exception("Index out of bounds");
            return 0.f;
        }
        return fullBuffer[i];
    }

}