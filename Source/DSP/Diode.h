/*
  ==============================================================================

    Diode.h
    Created: 10 Sep 2022 5:27:07pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Common/Constants.h"
#include "../Common/RingBuffer.h"

namespace WDYM {
    class Diode {
    public:
        Diode();
        ~Diode();
        void init(double sampleRate, int samplesPerBlock);
        void process(juce::AudioBuffer<float>& buffer, juce::AudioProcessorValueTreeState &apvts);
        static float waveshape(float x, juce::AudioProcessorValueTreeState& apvts);
        xynth::RingBuffer::maxmin_t readRingBuffer();
        float getRrStatus() { return rrStatus; };

    private:
        typedef struct {
            bool diode1 = true;
            bool diode2 = false;
            float vf = 0;
            float vb = 0;
            float trr = 0;
            float gain = 0;
            float sat = 0;
            float mix = 1;
        } DiodeProperties_t;

        static float wsAsym(float x, DiodeProperties_t& diodeProperties);
        static float wsSym(float x, DiodeProperties_t& diodeProperties);
        void setTrr(float trr);
        void recover(juce::AudioBuffer<float>& buffer);

        DiodeProperties_t diodeProperties;
        
        float samplesPerMs;
        int recoverScanner[2] = { 0, 0 };
        float lastSamples[2] = { 0, 0 };

        juce::dsp::LinkwitzRileyFilter<float> dcOffset;
        xynth::RingBuffer ringBuffer;

        std::vector<float> rr;
        float lastTrr;
        float rrStatus;
    };
}