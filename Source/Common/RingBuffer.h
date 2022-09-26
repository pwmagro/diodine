/*
  ==============================================================================

    RingBuffer.h
    Created: 6 Sep 2022 3:33:30pm
    Author:  thesp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace xynth
{
class RingBuffer
{
public:
    RingBuffer() = default;
    ~RingBuffer() = default;

    void prepare(juce::dsp::ProcessSpec& spec);
    void writeSamples(juce::dsp::AudioBlock<float>& buffer);
    typedef struct { float max; float min; } maxmin_t;
    maxmin_t readSamples();
    size_t getBufferSize() { return buffer.size(); }
    float getSample(int i);

private:
    std::vector<float> buffer;
    std::atomic<size_t> writeAtomic{ 0 };
    size_t read{ 0 };
};
} // namespace xynth